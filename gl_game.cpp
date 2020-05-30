#include "gl_game.h"
#include <QOpenGLShaderProgram>
#include <QTime>


GL_GAME::GL_GAME(QWidget *parent) : QGLWidget(parent)
{
}

GL_GAME::~GL_GAME()
{
}

void GL_GAME::initializeGL()
{
    initializeOpenGLFunctions();

    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    initShader();
    Cube =new GL_CUBE();
    glEnable(GL_DEPTH_TEST);


}
class Parallelepiped
{
public:
    QVector3D location;
    QVector3D size;
    QVector3D axis;
    float angular_rate;

    void set_location(float x,float y,float z)
    {
        location.setX(x);
        location.setY(y);
        location.setZ(z);
    }
    void set_size(float width,float heigh,float depth)
    {
        size.setX(width);
        size.setY(heigh);
        size.setZ(depth);
    }
    void set_angular_rate(float angular_rate_,float x,float y,float z)
    {
        angular_rate=angular_rate_;
        axis.setX(x);
        axis.setY(y);
        axis.setZ(z);
    }

};
#define numbr_part  200
void GL_GAME::paintGL()
{

    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    static Parallelepiped * particles=new Parallelepiped[numbr_part] ;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float cnt=0;
    if(cnt==0)
    {
        for(int i=0;i<numbr_part;i++)
        {
            particles[i].set_location(
                        60.0f*(qrand()/2147483647.0f-0.5f),
                        60.0f*(qrand()/2147483647.0f-0.5f),
                        -90.0f*qrand()/2147483647.0f);
            particles[i].set_size(
                        2.0f*qrand()/2147483647.0f,
                        2.0f*qrand()/2147483647.0f,
                        2.0f* qrand()/2147483647.0f);
            particles[i].set_angular_rate(10.0f*qrand()/2147483647.0f,qrand()/2147483647.0f,qrand()/2147483647.0f,qrand()/2147483647.0);
        }
    }

    for (int i=0;i<numbr_part;i++ )
    {
        Model_View.setToIdentity();
        Model_View.translate(particles[i].location.x(), particles[i].location.y(), particles[i].location.z());
        Model_View.rotate(particles[i].angular_rate*cnt,particles[i].axis);
        Model_View.scale(particles[i].size.x(), particles[i].size.y(), particles[i].size.z());
        program.setUniformValue("mvp_matrix",Projection*Model_View);
        Cube->drawCubeGeometry(&program);
    }

    update();
    cnt++;
}

void GL_GAME::initShader()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/VS.vsh"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/FS.fsh"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}



void GL_GAME::resizeGL(int width, int height)
{
    glViewport(0, 0, GLint(width), GLint(height));
    Projection.setToIdentity();

    double aspect = double(width) / double(height ? height : 1);
    const double zNear = 1.0, zFar = 100.0, fov = 90.0;
    Projection.setToIdentity();
    Projection.perspective(fov, aspect, zNear, zFar);

}
