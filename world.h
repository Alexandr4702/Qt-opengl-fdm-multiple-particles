#ifndef WORLD_H
#define WORLD_H

#include "body.h"
#include <QVector>

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <math.h>

class World:public QGLWidget
{
public:
    World(QGLContext * ctx);
    void add_body( Body*);
    void add_forces(float);
    /*brief:
     *param:
     *
     *
     *
    */
    void update(float dt);
    void draw();
    void draw(QMatrix4x4 & projection_matrix);
    void init_pos_oren_shader();
public:
    QVector<float> forces;
    QVector<Body*> bodies;
    QMatrix4x4 Projection;
    float dt=0.01;
    float time=0.0f;
    QOpenGLShaderProgram shader_position_orentation_programm;
    QOpenGLShaderProgram* getShader_position_orentation_programm() ;
    QMatrix4x4* getProjection();
    void setProjection(const QMatrix4x4 &value);
    QGLContext* ctx;
};

#endif // WORLD_H
