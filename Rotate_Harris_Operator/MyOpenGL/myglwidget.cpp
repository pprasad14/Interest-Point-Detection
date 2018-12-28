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
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.vert");
std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.tri");

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
    float a1, b1,c1;

    //  to count no of vertices
    cout << "Finding total number of vertices and faces in files:" << endl;
    while(inFile_vert >> a1 >> b1 >> c1)
    {
        n_vertex++;
    }
    cout << "No of vertices : " << n_vertex << endl;

    // to count the no of faces
    while(inFile_face >> a1 >> b1 >> c1)
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
    std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.vert");
    std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.tri");

    cout << "Populating Vertex Structure:" << endl;
    while(inFile_vert >> a1 >> b1 >> c1)
    {
        vertices[pos].x = a1;
        vertices[pos].y = b1;
        vertices[pos].z = c1;
        pos++;
    }
    cout << "No of iterations : " << pos << endl;
    cout << "Populating Vertex Structure successfull!!" << endl << endl;

    //populating the faces in the structure
    pos = 0;
    cout << "Populating Faces Structure:" << endl;

    while(inFile_face >> a1 >> b1 >> c1)
    {
        faces[pos].v1 = a1;
        faces[pos].v2 = b1;
        faces[pos].v3 = c1;
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

}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::read_points()
{
//    int n_vertex;
//    int n_face;

//    n_vertex = 0;
//    n_face = 0;
//    float a1, b1,c1;

//    //  to count no of vertices
//    cout << "Finding total number of vertices and faces in files:" << endl;
//    while(inFile_vert >> a1 >> b1 >> c1)
//    {
//        n_vertex++;
//    }
//    cout << "No of vertices : " << n_vertex << endl;

//    // to count the no of faces
//    while(inFile_face >> a1 >> b1 >> c1)
//    {
//        n_face++;
//    }
//    cout << "No of faces : " << n_face << endl << endl;

//    //creating structures to hold the vertices and faces
//    vertices = new vertex[n_vertex];
//    faces = new face[n_face];

//    //populating the vertices in the structure
//    int pos = 0;

//    // re-reading input file stream since it has already reached the EOF with previous iteration above
//    std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.vert");
//    std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.tri");

//    cout << "Populating Vertex Structure:" << endl;
//    while(inFile_vert >> a1 >> b1 >> c1)
//    {
//        vertices[pos].x = a1;
//        vertices[pos].y = b1;
//        vertices[pos].z = c1;
//        pos++;
//    }
//    cout << "No of iterations : " << pos << endl;
//    cout << "Populating Vertex Structure successfull!!" << endl << endl;

//    //populating the faces in the structure
//    pos = 0;
//    cout << "Populating Faces Structure:" << endl;

//    while(inFile_face >> a1 >> b1 >> c1)
//    {
//        faces[pos].v1 = a1;
//        faces[pos].v2 = b1;
//        faces[pos].v3 = c1;
//        pos++;
//    }
//    cout << "No of iterations : " << pos << endl;
//    cout << "Populating Faces Structure successfull!!" << endl << endl;

//    inFile_vert.close();
//    cout << "Vertex file closed!" << endl;

//    inFile_face.close();
//    cout << "Face file closed!" << endl;
//    this->vertices = vertices;
//    this->faces = faces;
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
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
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
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
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

    qglColor(Qt::red);
//    glBegin(GL_QUADS);
//        glNormal3f(0,0,1);
//        glVertex3f(-1,-1,0);
//        glVertex3f(-1,1,0);
//        glVertex3f(1,1,0);
//        glVertex3f(1,-1,0);
//    glEnd();

//    for(int i = 0; i < no_of_faces; i++)
//    {
//            glBegin(GL_TRIANGLES);
////                glNormal3f(0,-1,0.707);
//                glVertex3f(this->vertices[this->faces[i].v1].x ,this->vertices[this->faces[i].v1].y ,this->vertices[this->faces[i].v1].z );
//                glVertex3f(this->vertices[this->faces[i].v2].x ,this->vertices[this->faces[i].v2].y ,this->vertices[this->faces[i].v2].z );
//                glVertex3f(this->vertices[this->faces[i].v3].x ,this->vertices[this->faces[i].v3].y ,this->vertices[this->faces[i].v3].z );
//            glEnd();
//    }

    for(int i = 0; i < no_of_faces; i++)
    {
            glBegin(GL_TRIANGLES);
//                glNormal3f(0,-1,0.707);
                glVertex3f(vertices[faces[i].v1].x ,vertices[faces[i].v1].y ,vertices[faces[i].v1].z );
                glVertex3f(vertices[faces[i].v2].x ,vertices[faces[i].v2].y ,vertices[faces[i].v2].z );
                glVertex3f(vertices[faces[i].v3].x ,vertices[faces[i].v3].y ,vertices[faces[i].v3].z );
            glEnd();
    }


//    glBegin(GL_TRIANGLES);
//        glNormal3f(1,0, 0.707);
//        glVertex3f(1,-1,0);
//        glVertex3f(1,1,0);
//        glVertex3f(0,0,1.2);
//    glEnd();
//    glBegin(GL_TRIANGLES);
//        glNormal3f(0,1,0.707);
//        glVertex3f(1,1,0);
//        glVertex3f(-1,1,0);
//        glVertex3f(0,0,1.2);
//    glEnd();
//    glBegin(GL_TRIANGLES);
//        glNormal3f(-1,0,0.707);
//        glVertex3f(-1,1,0);
//        glVertex3f(-1,-1,0);
//        glVertex3f(0,0,1.2);
//    glEnd();
//    cout << endl << "testing: " << this->faces[1].v1 << endl;
}
