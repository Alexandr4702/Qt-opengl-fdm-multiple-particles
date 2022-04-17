#include "world.h"

World *for_calc;

World::World(QGLContext* ctx)
{
    ctx->makeCurrent();
    init_pos_oren_shader();
    Projection.setToIdentity();
    Projection.perspective(90, 1.0, 1, 90);
    for_calc = this;

    for_calc->calculation=QThread::create([]()
    {
        while(1)
        {
//            fprintf(stderr,"updtae\r\n");

            for_calc->update(0.000001);
        }
    }
    );
    for_calc->calculation->start();
}

World::~World()
{
    calculation->terminate();
}

void World::update(float dt_)
{
    K=0;
//    fprintf(stderr,"hello update \r\n");
    if(bodies.size()==0)return;

    int size=bodies.size();

    for(int i=0;i<size;i++)
    {
        Body* body=bodies[i];

        body->temporary_forces.clear();
        K+=body->mass*(body->linear_velocity*body->linear_velocity).length()/2.0;

        for (Body* body_test : bodies )
        {
            if(body==body_test)continue;

                QVector3D r=(body->position-body_test->position);
                if(r.length()==0)
                {continue;}
                QVector3D F=-body->mass*body_test->mass*r;
//                if((r.length()*r.length()*100-r.length()*r.length()*r.length())==0)continue;
                body->temporary_forces.push_back(F/r.length()/(r.length()*r.length()));
//                qDebug()<<F/r.length()<<r.length()<<r;
//                U+=
        }

        body->force_summ=QVector3D(0,0,0);

        for(QVector3D force :body->temporary_forces)
        {
            body->force_summ+=force;
        }

        for(QVector3D force : body->forces)
        {
            body->force_summ += force;
        }

        body->torque_summ = QVector3D(0,0,0);
        for(QVector3D torque : body->torques)
        {
            body->torque_summ += torque;
        }

         body->linear_acclereation=body->force_summ/body->mass;
         body->linear_velocity+=body->linear_acclereation*dt_;

        body->angular_velocity += body->angular_acceleration*dt_;

         float omega=body->angular_velocity.length();
//         QQuaternion M(cosf(omega*dt_/2.0f),sinf(omega*dt_/2.0f)*body->angular_velocity);
//         M.normalize();
         QQuaternion M(1,body->angular_velocity*dt_/2);

         body->orenation=M*body->orenation;
         body->position+=body->linear_velocity*dt;
    }

//    qDebug()<<K;
    time+=dt_;
}

void World::update()
{

}

void World::draw()
{
//    update(dt);
//    fprintf(stderr,"hello draw \r\n");

    cam.setToIdentity();
//    cam.lookAt(bodies[0]->position-QVector3D(0,-20,-100), bodies[0]->position, QVector3D(0,1,0));
    for(Body* body:bodies)
    {
        body->draw();
    }

}

void World::draw(QMatrix4x4 &projection_matrix)
{
    Q_UNUSED(projection_matrix);

    for(Body* body:bodies)
    {
        body->draw();
    }
}

void World::init_pos_oren_shader()
{

    if (!shader_position_orentation_programm.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/VS.vsh"))
        exit(-1);
    if (!shader_position_orentation_programm.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/FS.fsh"))
        exit(-1);

    if (!shader_position_orentation_programm.link())
        exit(-1);
    if (!shader_position_orentation_programm.bind())
        exit(-1);

}

QMatrix4x4* World::getProjection()
{
    return &Projection;
}

void World::setProjection(const QMatrix4x4 &value)
{
    Projection = value;
}

QOpenGLShaderProgram* World::getShader_position_orentation_programm()
{
    return &shader_position_orentation_programm;
}

void World::add_body(Body * body)
{
    body->set_projection(&Projection);
    body->set_cam(&cam);

    bodies.push_back(body);
}
