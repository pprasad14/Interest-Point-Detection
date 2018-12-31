// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <stdlib.h>
#include <fstream>


std::string line;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

//std::string line;
//using std::cout;
//using std::endl;
//using std::cin;
//using std::cerr;

std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.vert");
std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.tri");


//std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.vert");
//std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.tri");

//struct vertex {
//    float x;
//    float y;
//    float z;
//};

//struct face {
//    int v1;
//    int v2;
//    int v3;
//};

//vertex *vertices;
//face *faces;

#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    int n_vertex;
    int n_face;

    n_vertex = 0;
    n_face = 0;
    int a_face, b_face,c_face/*,d_face*/;
    float a_vert, b_vert,c_vert/*,d_vert*/;
//    int temp;


    //  to count no of vertices
    cout << "Finding total number of vertices and faces in files:" << endl;
    while(inFile_vert >> a_vert >> b_vert >> c_vert)
    {
        n_vertex++;
    }
    cout << "No of vertices : " << n_vertex << endl;

    // to count the no of faces
    while(inFile_face >> /*temp >>*/ a_face >> b_face >> c_face /*>> d1*/)
    {
        n_face++;
    }
    cout << "No of faces : " << n_face << endl << endl;

    //creating structures to hold the vertices and faces
    vertices = new vertex[n_vertex];
    faces = new face[n_face];

    //populating the vertices in the structure
    int pos = 0;

    // re-reading input file stream since it has already reached the EOF with previous iteration above

    std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.vert");
    std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.tri");

//        std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.vert");
//        std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.tri");


    cout << "Populating Vertex Structure:" << endl;
    while(inFile_vert >> a_vert >> b_vert >> c_vert)
    {
        vertices[pos].x = a_vert;
        vertices[pos].y = b_vert;
        vertices[pos].z = c_vert;
        pos++;
    }
    cout << "No of iterations : " << pos << endl;
    cout << "Populating Vertex Structure successfull!!" << endl << endl;

    //populating the faces in the structure
    pos = 0;
    cout << "Populating Faces Structure:" << endl;

    while(inFile_face >>/* temp >>*/ a_face >> b_face >> c_face /*>> d1*/)
    {
        faces[pos].v1 = a_face;
        faces[pos].v2 = b_face;
        faces[pos].v3 = c_face;
//        faces[pos].v4 = d1;
        pos++;
    }
    cout << "No of iterations : " << pos << endl;
    cout << "Populating Faces Structure successfull!!" << endl << endl;

    inFile_vert.close();
    cout << "Vertex file closed!" << endl;

    inFile_face.close();

    cout << "Face file closed!" << endl;

    this->vertices = vertices;
    this->faces = faces;

    this->no_of_faces = n_face;
    this->no_of_vertices = n_vertex;

    cout << endl << "test vertex:" << this->vertices[0].x << "  " << this->vertices[0].y  << "  " << this->vertices[0].z << endl;
    cout << endl << "test face:" << this->faces[0].v1 << "  " << this->faces[0].v2  << "  " << faces[0].v3 << endl;
    cout << endl << "test no vertex:" << this->no_of_vertices << endl;
    cout << endl << "test no faces:" << this->no_of_faces << endl;

//    for(int i = 0; i < n_vertex; i++){
//        cout << "test vertex:" << this->vertices[i].x << "  " << this->vertices[i].y  << "  " << this->vertices[i].z << endl;
//    }
//    for(int i = 0; i < n_face; i++){
//        cout << "test vertex:" << this->faces[i].v1 << "  " << this->faces[i].v2  << "  " << this->faces[i].v3 <<  "  " << this->faces[i].v4 << endl;
//    }


}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::read_points()
{

}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::blue);

//    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 10, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
//#else
//    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
//#endif

    glScalef(0.05f,0.05f,0.05f);
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::draw()
{

//    qglColor(Qt::red);
    //    glBegin(GL_QUADS);
    //        glNormal3f(0,0,1);
    //        glVertex3f(-1,-1,0);
    //        glVertex3f(-1,1,0);
    //        glVertex3f(1,1,0);
    //        glVertex3f(1,-1,0);
    //    glEnd();

    float Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;
    float norm;

    for(int i = 0; i < no_of_faces; i++)
    {

        // Finding the Normal Vector to a face:
        // https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal?fbclid=IwAR04iWPcnrtmCJ-Vxn_4jkO4vS9aJZqkmydLchUe4HQRL6mpSHeY2rAxzR8


        Ux = this->vertices[this->faces[i].v2].x  - this->vertices[this->faces[i].v1].x;
        Uy = this->vertices[this->faces[i].v2].y  - this->vertices[this->faces[i].v1].y;
        Uz = this->vertices[this->faces[i].v2].z  - this->vertices[this->faces[i].v1].z;

        Vx = this->vertices[this->faces[i].v3].x  - this->vertices[this->faces[i].v1].x;
        Vy = this->vertices[this->faces[i].v3].y  - this->vertices[this->faces[i].v1].y;
        Vz = this->vertices[this->faces[i].v3].z  - this->vertices[this->faces[i].v1].z;

        Nx = Uy*Vz - Uz*Vy;
        Ny = Uz*Vx - Ux*Vz;
        Nz = Ux*Vy - Uy*Vx;

        norm = sqrt(Nx*Nx + Ny+Ny + Nz*Nz);

        Nx = Nx/norm;
        Ny = Ny/norm;
        Nz = Nz/norm;


        glBegin(GL_TRIANGLES);
//        glNormal3f(Nx,Ny,Nz);
        glVertex3f(this->vertices[this->faces[i].v1].x /10 ,this->vertices[this->faces[i].v1].y /10,this->vertices[this->faces[i].v1].z /10 );
        glVertex3f(this->vertices[this->faces[i].v2].x /10,this->vertices[this->faces[i].v2].y /10,this->vertices[this->faces[i].v2].z /10 );
        glVertex3f(this->vertices[this->faces[i].v3].x /10,this->vertices[this->faces[i].v3].y /10,this->vertices[this->faces[i].v3].z /10);
//        glVertex3f(this->vertices[this->faces[i].v4].x ,this->vertices[this->faces[i].v4].y ,this->vertices[this->faces[i].v4].z );
        glEnd();

    }
//    for(int i = 0; i < no_of_faces; i++)
//    {
//        glBegin(GL_QUADS);
////        glNormal3f(0,-1,0.707);
//        glVertex3f(this->vertices[this->faces[i].v1].x ,this->vertices[this->faces[i].v1].y ,this->vertices[this->faces[i].v1].z );
//        glVertex3f(this->vertices[this->faces[i].v2].x ,this->vertices[this->faces[i].v2].y ,this->vertices[this->faces[i].v2].z );
//        glVertex3f(this->vertices[this->faces[i].v3].x ,this->vertices[this->faces[i].v3].y ,this->vertices[this->faces[i].v3].z );
//        glVertex3f(this->vertices[this->faces[i].v4].x ,this->vertices[this->faces[i].v4].y ,this->vertices[this->faces[i].v4].z );
//        glEnd();

//    }

    //    for(int i = 0; i < no_of_faces; i++)
    //    {
    //            glBegin(GL_TRIANGLES);
    //                glNormal3f(0,-1,0.707);
    //                glVertex3f(vertices[faces[i].v1].x ,vertices[faces[i].v1].y ,vertices[faces[i].v1].z );
    //                glVertex3f(vertices[faces[i].v2].x ,vertices[faces[i].v2].y ,vertices[faces[i].v2].z );
    //                glVertex3f(vertices[faces[i].v3].x ,vertices[faces[i].v3].y ,vertices[faces[i].v3].z );
    //            glEnd();
    //    }

}
