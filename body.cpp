#include "body.h"

Body::Body(QGLContext* ctx_):ctx(ctx_)
{
    Assimp::Importer importer;
    QString pathToFile;

    const aiScene* scene = importer.ReadFile(pathToFile.toStdString(),
            aiProcess_GenSmoothNormals |
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType
            );

    if (!scene)
    {
        qDebug() << "Error loading file: (assimp:) " << importer.GetErrorString();
        return;
    }
}

Body::Body(const Body &other)
{
    position = other.position;
    orenation = other.orenation;
    scale = other.scale;

    linear_velocity = other.linear_velocity;
    angular_velocity = other.angular_velocity;

    angular_acceleration = other.angular_acceleration;
    linear_acclereation = other.linear_acclereation;
    density = other.density;
    Volume = other.Volume;
    mass = other.mass;
    ctx = other.ctx;
}

Body::Body(Body &&other) noexcept
{
    position = other.position;
    orenation = other.orenation;
    scale = other.scale;
    linear_velocity = other.linear_velocity;
    angular_velocity = other.angular_velocity;

    angular_acceleration=other.angular_acceleration;
    linear_acclereation=other.linear_acclereation;

    density=other.density;
    Volume=other.Volume;
    mass=other.mass;
    ctx=other.ctx;

}

Body &Body::operator=(const Body &other)
{
    if (this == &other)
        return *this;
    position=other.position;
    orenation=other.orenation;
    scale=other.scale;

    linear_velocity=other.linear_velocity;
    angular_velocity=other.angular_velocity;

    angular_acceleration=other.angular_acceleration;
    linear_acclereation=other.linear_acclereation;

    density=other.density;
    Volume=other.Volume;
    mass=other.mass;
    ctx=other.ctx;
    return *this;
}

Body &Body::operator=(Body &&other) noexcept
{
    if (this == &other)
        return *this;
    position=other.position;
    orenation=other.orenation;
    scale=other.scale;

    linear_velocity=other.linear_velocity;
    angular_velocity=other.angular_velocity;

    angular_acceleration=other.angular_acceleration;
    linear_acclereation=other.linear_acclereation;

    density=other.density;
    Volume=other.Volume;
    mass=other.mass;
    ctx=other.ctx;
    return *this;
}

QVector3D Body::getScale() const
{
    return scale;
}

void Body::setScale(const QVector3D &value)
{
    scale = value;
}


void Body::set_orenatation(const QQuaternion &oreantation)
{
    orenation=oreantation;
}

QVector3D Body::getPosition() const
{
    return position;
}

void Body::setPosition(const QVector3D &value)
{
    position = value;
}



void Body::init_geometry()
{

}

void Body::draw()
{

}

void Body::set_projection(QMatrix4x4 *)
{

}

void Body::set_cam(QMatrix4x4 *)
{

}

void Body::set_context(QGLContext *ctx_)
{
    ctx=ctx_;
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
