#ifndef GL_GAME_H
#define GL_GAME_H

#include <QGLWidget>
#include <QtOpenGL>
#include "gl_cube.h"
#include "world.h"

class GL_GAME: public QGLWidget, public QOpenGLFunctions
{
public:
    GL_GAME(QWidget *parent);
    ~GL_GAME();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void initShader();
private:
    GL_CUBE* Cube;
    World* world;

};

#endif // GL_GAME_H
