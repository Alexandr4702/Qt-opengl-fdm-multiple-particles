#include "world.h"

World::World(QGLContext* ctx)
{
    ctx->makeCurrent();
    init_pos_oren_shader();
    Projection.setToIdentity();
    Projection.perspective(90,1.0,1,90);

}

void World::update(float dt_)
{
    for(Body* body:bodies)
    {
        body->temporary_forces.clear();


        for (Body* body_test:bodies )
        {
                QVector3D r=(body->position-body_test->position);
                body->temporary_forces.push_back(-body->mass*body_test->mass*r);
        }

        body->force_summ=QVector3D(0,0,0);

        for(QVector3D force :body->temporary_forces)
        {
            body->force_summ+=force;
        }

        for(QVector3D force :body->forces)
        {
            body->force_summ+=force;
        }

        body->torque_summ=QVector3D(0,0,0);
        for(QVector3D torque :body->torques)
        {
            body->torque_summ+=torque;
        }

         body->linear_acclereation=body->force_summ/body->mass;
         body->linear_velocity+=body->linear_acclereation*dt_;



//         body->angular_acceleration=;
        body->angular_velocity+=body->angular_acceleration*dt_;

         float omega=body->angular_velocity.length();
         QQuaternion M(cosf(omega*dt_/2.0f),sinf(omega*dt_/2.0f)*body->angular_velocity);
         M.normalize();
         body->orenation=M*body->orenation;
         body->position+=body->linear_velocity*dt;

    }
    cam.setToIdentity();
    cam.lookAt(QVector3D(0,0,0),bodies[0]->position,QVector3D(0,1,0));


    time+=dt_;

}

void World::update()
{
    for(Body* body:bodies)
    {
                body->setPosition(QVector3D(0,0,-10));
                body->set_orenatation(QQuaternion(time*1000,1.0f,0.0f,0.0f));
                body->setScale(QVector3D(1,1,2));
    }
    time+=dt;
}

void World::draw()
{
    update(dt);

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
        exit(1);
    if (!shader_position_orentation_programm.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/FS.fsh"))
        exit(1);

    if (!shader_position_orentation_programm.link())
        exit(1);


    if (!shader_position_orentation_programm.bind())
        exit(1);

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
