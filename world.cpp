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
    for(Body body:bodies)
    {
                body.setPosition(QVector3D(0,0,-20));
                body.set_orenatation(QQuaternion(time,0.0f,0.0f,1.0f));

    }
    time+=dt_;

}

void World::update()
{
    for(Body body:bodies)
    {
                body.setPosition(QVector3D(0,0,-10));
                body.set_orenatation(QQuaternion(time*1000,1.0f,0.0f,0.0f));
                body.setScale(QVector3D(1,1,2));
    }
    time+=dt;
}

void World::draw()
{
    update();

    for(Body body:bodies)
    {
        body.draw();
    }
}

void World::draw(QMatrix4x4 &projection_matrix)
{
    Q_UNUSED(projection_matrix);

    for(Body body:bodies)
    {
        body.draw();
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



void World::add_body(Body & body)
{
    body.set_projection(&Projection);
    bodies.push_back(body);
}

void World::add_body(Body && body)
{
    body.set_projection(&Projection);
    bodies.push_back(body);
}
