#ifndef GL_CUBE_H
#define GL_CUBE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QGLWidget>

#include "body.h"

class GL_CUBE: public Body
{
public:
    GL_CUBE(QOpenGLShaderProgram *program,QGLContext* ctx_);
    GL_CUBE(const GL_CUBE& other);
    GL_CUBE(GL_CUBE&& other)noexcept;
    GL_CUBE& operator=(const GL_CUBE& other);
    GL_CUBE& operator=(GL_CUBE&& other)noexcept;
    virtual ~GL_CUBE();

    void draw()override;
    void init_geometry ()override;
    void set_projection(QMatrix4x4*)override;
    void set_cam(QMatrix4x4*)override;

private:

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QMatrix4x4 Model_View;
    QMatrix4x4* Projection;
    QMatrix4x4* cam;
    QOpenGLShaderProgram* program;
    int vertexLocation;
//-----------------------------------------------------------------
     QVector<QVector3D> ver;
     QVector <GLushort> indeces;
};


#endif // GL_CUBE_H
