#include "world.h"

World::World(QGLContext* ctx)
{
    ctx->makeCurrent();
    initializeOpenGLFunctions();
    init_pos_oren_shader();
    Projection.setToIdentity();
    Projection.perspective(90,1.5,1,90);

}

void World::update(float dt)
{
    for(Body* body:bodies)
    {

    }
}

void World::draw()
{

    for(Body* body:bodies)
    {
        body->draw();
    }
    time+=dt;
}

void World::draw(QMatrix4x4 &projection_matrix)
{
    for(Body* body:bodies)
    {
        body->draw();
    }
}

void World::init_pos_oren_shader()
{

    if (!shader_position_orentation_programm.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/VS.vsh"))
        close();

    // Compile fragment shader
    if (!shader_position_orentation_programm.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/FS.fsh"))
        close();

    // Link shader pipeline
    if (!shader_position_orentation_programm.link())
        close();

    // Bind shader pipeline for use
    if (!shader_position_orentation_programm.bind())
        close();

//    qDebug()<<shader_position_orentation_programm.;
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
    bodies.push_back(body);
}
