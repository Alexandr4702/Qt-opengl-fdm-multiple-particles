#include "world.h"

World::World()
{

}

void World::update(float dt)
{
    for(Body* body:bodies)
    {

    }
}

void World::draw()
{
    for(Body* body:bodies)
    {
        body->draw();
    }
}

void World::add_body(Body * body)
{
    bodies.push_back(body);
}
