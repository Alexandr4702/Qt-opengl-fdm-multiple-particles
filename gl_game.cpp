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

    Body* ptr= new GL_CUBE(
                &world->shader_position_orentation_programm,context());
    ptr->setPosition(QVector3D(0,0,-10));
    ptr->forces.push_back(QVector3D(0,0,0));
    ptr->angular_acceleration=QVector3D(0,0.1,10);
    ptr->setMass(200);
    ptr->J.setToIdentity();
    world->add_body(ptr);

    for (int i=0;i<20 ;i++ ) {
        ptr=new GL_CUBE(&world->shader_position_orentation_programm,context());
        ptr->setPosition(QVector3D(-i*5,-3,-10));
//        ptr->forces.push_back(QVector3D(0,-20,0));
        world->add_body(ptr);

    }

    for (int i=0;i<20 ;i++ ) {
        ptr=new GL_CUBE(&world->shader_position_orentation_programm,context());
        ptr->setPosition(QVector3D(-i*5,3,-10));
//        ptr->forces.push_back(QVector3D(0,-20,0));
        world->add_body(ptr);

    }

    for (int i=0;i<20 ;i++ ) {
        ptr=new GL_CUBE(&world->shader_position_orentation_programm,context());
        ptr->setPosition(QVector3D(-i*5,3,-5));
//        ptr->forces.push_back(QVector3D(0,-20,0));
        world->add_body(ptr);
    }


    for (int i=0;i<20 ;i++ ) {
        ptr=new GL_CUBE(&world->shader_position_orentation_programm,context());
        ptr->setPosition(QVector3D(-i*5,-3,-5));
//        ptr->forces.push_back(QVector3D(0,-20,0));
        world->add_body(ptr);
    }



}

void GL_GAME::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    static int cnt=0;
//    qsrand(QTime::currentTime().msecsSinceStartOfDay());


    world->draw();

    update();
    cnt++;
}




void GL_GAME::resizeGL(int width, int height)
{
    glViewport(0, 0, GLint(width), GLint(height));
    world->Projection.setToIdentity();

    double aspect = double(width) / double(height ? height : 1);
    const double zNear = 1.0, zFar = 200.0, fov = 90.0;
    world->Projection.setToIdentity();
    world->Projection.perspective(fov, aspect, zNear, zFar);

}
