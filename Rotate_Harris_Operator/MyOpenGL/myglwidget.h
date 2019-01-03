// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>


//*************************************************
#include "window.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//std::string line;
//using std::cout;
//using std::endl;
//using std::cin;
//using std::cerr;

//std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.vert");
//std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.tri");

struct vertex {
    float x;
    float y;
    float z;
};

struct face {
    int v1;
    int v2;
    int v3;
//    int v4;
};

////vertex *vertices;
////face *faces;

////*************************************************


class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    vertex *vertices;
    face *faces;

    int no_of_vertices;
    int no_of_faces;

    int* interest_vertices;
    int h_no_of_interest_points;


    void read_points();

    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
signals:

public slots:

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void draw();

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;
};

#endif // MYGLWIDGET_H

