#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string line;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

std::ifstream inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.vert");
std::ifstream inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\cat0.tri");

struct vertex {
    float x;
    float y;
    float z;
};

struct face {
    int v1;
    int v2;
    int v3;
};

vertex *vertices;
face *faces;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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

//    MainWindow w;
//    w.show();

    return a.exec();
}
