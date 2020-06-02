#ifndef WORLD_H
#define WORLD_H

#include "body.h"
#include <QVector>

class World
{
public:
    World();
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
public:
    QVector<float> forces;
    QVector<Body*> bodies;
    float dt;

};

#endif // WORLD_H
