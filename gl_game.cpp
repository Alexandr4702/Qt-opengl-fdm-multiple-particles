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
    initializeOpenGLFunctions();

    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    initShader();
    glEnable(GL_DEPTH_TEST);

    world.add_body(new GL_CUBE());

}

void GL_GAME::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    static int cnt=0;
    qsrand(QTime::currentTime().msecsSinceStartOfDay());

    world.draw();

    update();
    cnt++;
}

void GL_GAME::initShader()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/VS.vsh"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/FS.fsh"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}



void GL_GAME::resizeGL(int width, int height)
{
    glViewport(0, 0, GLint(width), GLint(height));
    Projection.setToIdentity();

    double aspect = double(width) / double(height ? height : 1);
    const double zNear = 1.0, zFar = 100.0, fov = 90.0;
    Projection.setToIdentity();
    Projection.perspective(fov, aspect, zNear, zFar);

}
