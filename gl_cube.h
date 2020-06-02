#ifndef GL_CUBE_H
#define GL_CUBE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QGLWidget>

#include "body.h"

class GL_CUBE: protected QOpenGLFunctions , public Body, public QGLWidget
{
public:
    GL_CUBE();
    GL_CUBE(QOpenGLShaderProgram *program);
    virtual ~GL_CUBE();

    void draw()override;
    void init_geometry ()override;

    void init_shader();

private:

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLShaderProgram program;
};

#endif // GL_CUBE_H
