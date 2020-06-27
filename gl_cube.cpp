#include "gl_cube.h"
#include <QGLWidget>
#include <QtOpenGL>

GL_CUBE::GL_CUBE():indexBuf(QOpenGLBuffer::IndexBuffer),Body((QGLContext*)(12))
{



}

GL_CUBE::~GL_CUBE()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

GL_CUBE::GL_CUBE(QOpenGLShaderProgram *program,QGLContext* ctx_):Body(ctx_),
    program(program)
{
    ctx->makeCurrent();
    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    init_geometry();

    init_shader();
}


void GL_CUBE::init_geometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
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

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

//! [1]
    // Transfer vertex data to VBO 0

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(QVector3D));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
    //! [1]
}

void GL_CUBE::set_projection(QMatrix4x4 * projection_)
{
    Projection=projection_;
}

void GL_CUBE::init_shader()
{

}
void GL_CUBE::draw()
{

    //--------------------------------------------------------------
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glFrustum(-1.0,1.0, -1.0, 1.0, 1.0, 20.0);
//    //--------------------------------------------------------------
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(0.0,0.0,-2.0);
//    glRotatef(20,1,0.5,0);


//    glBegin(GL_LINES);
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex3f( 0.0,  0.0, 0.0);
//    glVertex3f(1.0,0.0,0.0);
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f( 0.0,  0.0, 0.0);
//    glVertex3f(0.0,1.0,0.0);
//    glColor3f(0.0, 0.0, 1.0);
//    glVertex3f( 0.0,  0.0, 0.0);
//    glVertex3f(0.0,0.0,1.0);
//    glEnd();
//return;

    position=QVector3D(0,0,-5);


    Model_View.setToIdentity();
    Model_View.translate(position.x(),position.y(),position.z());
//    Model_View.rotate();
    Model_View.scale(1,1,1);

    QMatrix4x4 test=*Projection*Model_View;


    program->setUniformValue("mvp_matrix",test);

    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}

