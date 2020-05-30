#ifndef BODY_H
#define BODY_H
#include <QVector3D>

class Body
{
public:
    Body();
    QVector3D position;
    QQuaternion orenation();

    QVector3D linear_velocity;
    QVector3D angular_velocity;


    QVector3D angular_acceleration;
    QVector3D linear_acclereation;

    QVector3D force;
    QVector3D torque;

    double density;
    double Volume;
    double mass;


    void set_location(const QVector3D& location);
    void set_orenatation(const QQuaternion& oreantation);




    double getDensity() const;
    void setDensity(double value);
    double getVolume() const;
    void setVolume(double value);
    double getMass() const;
    void setMass(double value);
    QVector3D getLinear_velocity() const;
    void setLinear_velocity(const QVector3D &value);
    QVector3D getAngular_velocity() const;
    void setAngular_velocity(const QVector3D &value);
    QVector3D getAngular_acceleration() const;
    void setAngular_acceleration(const QVector3D &value);
    QVector3D getLinear_acclereation() const;
    void setLinear_acclereation(const QVector3D &value);
    QVector3D getForce() const;
    void setForce(const QVector3D &value);
    QVector3D getTorque() const;
    void setTorque(const QVector3D &value);
};

#endif // BODY_H
