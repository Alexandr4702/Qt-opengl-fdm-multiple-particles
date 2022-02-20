#include "gl_cube.h"
#include <QGLWidget>
#include <QtOpenGL>
#include <iostream>

GL_CUBE::~GL_CUBE()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

GL_CUBE::GL_CUBE(QOpenGLShaderProgram *program,QGLContext* ctx_):Body(ctx_),indexBuf(QOpenGLBuffer::IndexBuffer),
    program(program)
{
    ctx->makeCurrent();
    arrayBuf.create();
    indexBuf.create();

    init_geometry();
}

void GL_CUBE::set_cam(QMatrix4x4* cam_)
{
    cam=cam_;
}

GL_CUBE::GL_CUBE(const GL_CUBE &other):Body(other),indexBuf(QOpenGLBuffer::IndexBuffer)
{
    ctx->makeCurrent();

    arrayBuf.create();
    indexBuf.create();

    arrayBuf = other.arrayBuf;
    indexBuf = other.indexBuf;
    Model_View = other.Model_View;
    Projection = other.Projection;
    program = other.program;
}

GL_CUBE::GL_CUBE(GL_CUBE &&other) noexcept
    :Body(other)
{
    ctx->makeCurrent();

    arrayBuf.create();
    indexBuf.create();

    arrayBuf = other.arrayBuf;
    indexBuf = other.indexBuf;
    Model_View = other.Model_View;
    Projection = other.Projection;
    program = other.program;

    other.arrayBuf.destroy();
    other.indexBuf.destroy();
}

GL_CUBE &GL_CUBE::operator=(const GL_CUBE &other)
{
    if (this == &other)
        return *this;
    arrayBuf = other.arrayBuf;
    indexBuf = other.indexBuf;
    Model_View = other.Model_View;
    Projection = other.Projection;
    program = other.program;

    return *this;
}

GL_CUBE &GL_CUBE::operator=(GL_CUBE &&other) noexcept
{
    if (this == &other)
        return *this;
    arrayBuf = other.arrayBuf;
    indexBuf = other.indexBuf;
    Model_View = other.Model_View;
    Projection = other.Projection;
    program = other.program;

    other.arrayBuf.destroy();
    other.indexBuf.destroy();
    return *this;
}


void GL_CUBE::init_geometry()
{
    if(indeces.size() == 0)
    {
        QFile fl("./sphere.obj");
        if(!fl.open(QIODevice::OpenModeFlag::ReadOnly))
        {
            perror("Can't open file\n");
            exit(-1);
        }
        else
        {
            while (!fl.atEnd())
            {
                QByteArray line = fl.readLine();
                if(line[0] == 'v')
                {
                    float data[3];
                    int result = sscanf(line.data() + 1, "%f %f %f", data, data + 1, data + 2);
                    if(result != 3)
                    {
                        std::cerr << "Error while reading obj file " << result << "\r\n" << std::endl;
                        exit(-1);
                    }
                    QVector3D vertex(data[0], data[1], data[2]);
                    ver.push_back(vertex);
                }
                if(line[0] == 'f')
                {
                    GLushort data[3];
                    int result = sscanf(line.data() + 1, "%hu %hu %hu", data, data + 1, data + 2);
                    if(result != 3)
                    {
                        std::cerr << "Error while reading obj file " << result << " \r\n" << std::endl;
                        exit(-1);
                    }
                    indeces.push_back(data[0] - 1);
                    indeces.push_back(data[1] - 1);
                    indeces.push_back(data[2] - 1);
                }
            }
            fl.close();
        }
    }
    else{
        qDebug()<<"import \r\n";
    }

//! [1]
    arrayBuf.bind();
    arrayBuf.allocate(ver.data(), ver.size() * sizeof(QVector3D));

    indexBuf.bind();
    indexBuf.allocate(indeces.data(), indeces.size() * sizeof(GLushort));
    //! [1]
    vertexLocation = program->attributeLocation("a_position");
}

void GL_CUBE::set_projection(QMatrix4x4 * projection_)
{
    Projection=projection_;
}


void GL_CUBE::draw()
{
    Model_View.setToIdentity();
    Model_View.translate(position);
    Model_View.rotate(orenation);
    Model_View.scale(scale);

    QMatrix4x4 test=*Projection*(*cam)*Model_View;

    program->setUniformValue("mvp_matrix",test);

    arrayBuf.bind();
    indexBuf.bind();

    quintptr offset = 0;

    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    glDrawElements(GL_TRIANGLE_STRIP, indeces.size(), GL_UNSIGNED_SHORT, 0);
}

