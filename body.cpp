#include "body.h"

Body::Body()
{

}

QVector3D Body::getTorque() const
{
    return torque;
}

void Body::setTorque(const QVector3D &value)
{
    torque = value;
}

void Body::init_geometry()
{

}

void Body::draw()
{

}

QVector3D Body::getForce() const
{
    return force;
}

void Body::setForce(const QVector3D &value)
{
    force = value;
}

QVector3D Body::getLinear_acclereation() const
{
    return linear_acclereation;
}

void Body::setLinear_acclereation(const QVector3D &value)
{
    linear_acclereation = value;
}

QVector3D Body::getAngular_acceleration() const
{
    return angular_acceleration;
}

void Body::setAngular_acceleration(const QVector3D &value)
{
    angular_acceleration = value;
}

QVector3D Body::getAngular_velocity() const
{
    return angular_velocity;
}

void Body::setAngular_velocity(const QVector3D &value)
{
    angular_velocity = value;
}

QVector3D Body::getLinear_velocity() const
{
    return linear_velocity;
}

void Body::setLinear_velocity(const QVector3D &value)
{
    linear_velocity = value;
}

double Body::getMass() const
{
    return mass;
}

void Body::setMass(double value)
{
    mass = value;
}

double Body::getVolume() const
{
    return Volume;
}

void Body::setVolume(double value)
{
    Volume = value;
}

double Body::getDensity() const
{
    return density;
}

void Body::setDensity(double value)
{
    density = value;
}
