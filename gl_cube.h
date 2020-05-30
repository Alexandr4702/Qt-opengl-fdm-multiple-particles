#ifndef GL_CUBE_H
#define GL_CUBE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GL_CUBE: protected QOpenGLFunctions
{
public:
    GL_CUBE();
    virtual ~GL_CUBE();

    void drawCubeGeometry(QOpenGLShaderProgram *program);

private:
    void initCubeGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // GL_CUBE_H
