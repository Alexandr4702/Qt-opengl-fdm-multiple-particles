#include "gl_game.h"
#include <QOpenGLShaderProgram>
#include <QTime>


GL_GAME::GL_GAME(QWidget *parent) : QGLWidget(parent)
{

}

GL_GAME::~GL_GAME()
{

}

void GL_GAME::initializeGL()
{


    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    world=new World(context());

//    GL_CUBE cube(&world->shader_position_orentation_programm,context());
    world->add_body(GL_CUBE(&world->shader_position_orentation_programm,context()));

}

void GL_GAME::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    world->draw();
    update();
}




void GL_GAME::resizeGL(int width, int height)
{
    glViewport(0, 0, GLint(width), GLint(height));
    world->Projection.setToIdentity();

    double aspect = double(width) / double(height ? height : 1);
    const double zNear = 1.0, zFar = 100.0, fov = 90.0;
    world->Projection.setToIdentity();
    world->Projection.perspective(fov, aspect, zNear, zFar);

}
