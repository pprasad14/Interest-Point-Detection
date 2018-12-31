#include "harrisoperatorresponse.h"

#include <QtOpenGL>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <set>


std::string h_line;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;


std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.vert");
std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.tri");


//std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.vert");
//std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.tri");


HarrisOperatorResponse::HarrisOperatorResponse()
{
    populate_data();
    getNeighboorhood(1);
}

HarrisOperatorResponse::~HarrisOperatorResponse()
{

}

void HarrisOperatorResponse::getNeighboorhood(int k_rings)
{
    int i;
    //    set<int> neighbors;
    std::set<int> neighbors;
    std::set<int>::iterator it;
    int vertex = 1;

    for(i = 0; i < h_no_of_faces; i++){
        if((h_faces[i].v1 == vertex) || (h_faces[i].v2 == vertex) || (h_faces[i].v3 == vertex)){
            neighbors.insert(h_faces[i].v1);
            neighbors.insert(h_faces[i].v2);
            neighbors.insert(h_faces[i].v3);
        }
    }
    std::cout << endl << "myset contains:";
      for (it=neighbors.begin(); it!=neighbors.end(); ++it)
        std::cout << ' ' << *it;
      std::cout << '\n';



}

void HarrisOperatorResponse:: populate_data()
{
    int n_vertex;
    int n_face;

    n_vertex = 0;
    n_face = 0;
    int a_face, b_face,c_face/*,d_face*/;
    float a_vert, b_vert,c_vert/*,d_vert*/;
    //    int temp;


    //  to count no of vertices
    cout << "Finding total number of vertices and faces in files:" << endl;
    while(h_inFile_vert >> a_vert >> b_vert >> c_vert)
    {
        n_vertex++;
    }
    cout << "No of vertices : " << n_vertex << endl;

    // to count the no of faces
    while(h_inFile_face >> /*temp >>*/ a_face >> b_face >> c_face /*>> d1*/)
    {
        n_face++;
    }
    cout << "No of faces : " << n_face << endl << endl;

    //creating structures to hold the vertices and faces
    h_vertices = new Harris_vertices[n_vertex];
    h_faces = new Harris_faces [n_face];

    //populating the vertices in the structure
    int pos = 0;

    // re-reading input file stream since it has already reached the EOF with previous iteration above

    std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.vert");
    std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.tri");

    //        std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.vert");
    //        std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.tri");


    cout << "Populating Vertex Structure:" << endl;
    while(h_inFile_vert >> a_vert >> b_vert >> c_vert)
    {
        h_vertices[pos].x = a_vert;
        h_vertices[pos].y = b_vert;
        h_vertices[pos].z = c_vert;
        pos++;
    }
    cout << "No of iterations : " << pos << endl;
    cout << "Populating Vertex Structure successfull!!" << endl << endl;

    //populating the faces in the structure
    pos = 0;
    cout << "Populating Faces Structure:" << endl;

    while(h_inFile_face >>/* temp >>*/ a_face >> b_face >> c_face /*>> d1*/)
    {
        h_faces[pos].v1 = a_face;
        h_faces[pos].v2 = b_face;
        h_faces[pos].v3 = c_face;
        //        faces[pos].v4 = d1;
        pos++;
    }
    cout << "No of iterations : " << pos << endl;
    cout << "Populating Faces Structure successfull!!" << endl << endl;

    h_inFile_vert.close();
    cout << "Vertex file closed!" << endl;

    h_inFile_face.close();

    cout << "Face file closed!" << endl;

    this->h_vertices = h_vertices;
    this->h_faces = h_faces;

    this->h_no_of_faces = n_face;
    this->h_no_of_vertices = n_vertex;

    cout << endl << "HARRIS OUTPUT!!!" << endl;
    cout << endl << "h_test vertex:" << this->h_vertices[0].x << "  " << this->h_vertices[0].y  << "  " << this->h_vertices[0].z << endl;
    cout << endl << "h_test face:" << this->h_faces[0].v1 << "  " << this->h_faces[0].v2  << "  " << h_faces[0].v3 << endl;
    cout << endl << "h_test no vertex:" << this->h_no_of_vertices << endl;
    cout << endl << "h_test no faces:" << this->h_no_of_faces << endl;

}

//void HarrisOperatorResponse::populate_data(Harris_faces *f, Harris_vertices *v, int f_len, int v_len)
//{
//    this->no_of_faces = f_len;
//    this->no_of_vertices = v_len;

//    this->h_faces = f;
//    this->h_vertices = v;
//}
