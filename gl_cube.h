#ifndef GL_CUBE_H
#define GL_CUBE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QGLWidget>

#include "body.h"

class GL_CUBE: public Body, public QGLWidget
{
public:
    GL_CUBE();
    GL_CUBE(QOpenGLShaderProgram *program,QGLContext* ctx_);
    virtual ~GL_CUBE();

    void draw()override;
    void init_geometry ()override;
    void set_projection(QMatrix4x4*)override;

    void init_shader();

private:

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QMatrix4x4 Model_View;
    QMatrix4x4* Projection;
    QOpenGLShaderProgram* program;
};


#endif // GL_CUBE_H
