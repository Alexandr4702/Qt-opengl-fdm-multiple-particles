#include "gl_cube.h"
#include <QGLWidget>
#include <QtOpenGL>



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

    arrayBuf=other.arrayBuf;
    indexBuf=other.indexBuf;
    Model_View=other.Model_View;
    Projection=other.Projection;
    program=other.program;
}

GL_CUBE::GL_CUBE(GL_CUBE &&other) noexcept
    :Body(other)
{
    ctx->makeCurrent();

    arrayBuf.create();
    indexBuf.create();

    arrayBuf=other.arrayBuf;
    indexBuf=other.indexBuf;
    Model_View=other.Model_View;
    Projection=other.Projection;
    program=other.program;

    other.arrayBuf.destroy();
    other.indexBuf.destroy();
}

GL_CUBE &GL_CUBE::operator=(const GL_CUBE &other)
{
    if (this == &other)
        return *this;
    arrayBuf=other.arrayBuf;
    indexBuf=other.indexBuf;
    Model_View=other.Model_View;
    Projection=other.Projection;
    program=other.program;

    return *this;
}

GL_CUBE &GL_CUBE::operator=(GL_CUBE &&other) noexcept
{
    if (this == &other)
        return *this;
    arrayBuf=other.arrayBuf;
    indexBuf=other.indexBuf;
    Model_View=other.Model_View;
    Projection=other.Projection;
    program=other.program;


    other.arrayBuf.destroy();
    other.indexBuf.destroy();

    return *this;
}


void GL_CUBE::init_geometry()
{

    QVector3D vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f)}  // v23
    };

    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

//! [1]

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(QVector3D));

    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
    //! [1]
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

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}

