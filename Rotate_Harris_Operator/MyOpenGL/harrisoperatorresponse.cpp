#include "harrisoperatorresponse.h"

#include <QtOpenGL>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <set>
#include<algorithm>
#include<vector>


std::string h_line;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;


std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.vert");
std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.tri");

//std::ifstream h_inFile_int_points("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\Apple.ini.txt");


//std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.vert");
//std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.tri");


HarrisOperatorResponse::HarrisOperatorResponse()
{
    cout << endl << "Constructor: Harris: Populating Data:" << endl;
//    populate_data();
//    getNeighboorhood();
}

HarrisOperatorResponse::~HarrisOperatorResponse()
{

}

void HarrisOperatorResponse::getNeighboorhood()
{
    int k, i;
//    //    set<int> neighbors;
//    std::set<int> neighbors;
//    std::set<int>::iterator it;
////    int vertex = 1;

    //finding the first ring neighboorhood of all vertices:
    for(k = 0; k < h_no_of_vertices; k++){
        for(i = 0; i < h_no_of_faces; i++){
            if((h_faces[i].v1 == k) || (h_faces[i].v2 == k) || (h_faces[i].v3 == k)){
               h_vertices[k].first_ring_points.insert(h_faces[i].v1);
               h_vertices[k].first_ring_points.insert(h_faces[i].v2);
               h_vertices[k].first_ring_points.insert(h_faces[i].v3);
            }
        }

        // to remove the vertex whose neighborhood was calculated
//        it=neighbors.begin();
//        neighbors.erase(it);

////        std::cout << endl << "Neighbors of vertex no " << k << ":";
////        for (it=neighbors.begin(); it!=neighbors.end(); ++it)
////            std::cout << ' ' << *it;
////        std::cout << '\n';

//        neighbors.clear();

    }
}

std::set<int> HarrisOperatorResponse::selected_neighborhood(int index)
{
    std::set<int> ringhood ;
    for(int i=0; i<h_no_of_faces;i++)
    {

        if(h_faces[i].v1 == index)
        {
            ringhood.insert(h_faces[i].v2);
            ringhood.insert(h_faces[i].v3);
        }
        else if(h_faces[i].v2 == index)
        {
            ringhood.insert(h_faces[i].v1);
            ringhood.insert(h_faces[i].v3);
        }
        else if(h_faces[i].v3 == index)
        {
            ringhood.insert(h_faces[i].v1);
            ringhood.insert(h_faces[i].v2);
        }
    }


    return ringhood;
}


void HarrisOperatorResponse::display_ringhood(std::set<int> ringhood)
{
    std::set<int>::iterator it;
    for(it = ringhood.begin(); it!=ringhood.end(); it++)
    {
        std::cout<<*it<<" ";
    }

}

std::set<int> HarrisOperatorResponse::get_k_ringhood(Harris_vertices h_vertices, int k)
{
//    HarrisOperatorResponse x(Dir);
    std::set<int>::iterator ita,itx, itp;
    std::set<int> tmp, ringhood;
    std::vector<int> tmp2;
    // k = norings;
    std::set<int> k_ringhood, final_ring,k1_ringhood;
    std::set<int>::iterator it;

    if(k ==0){
        cout<<"Error. K has to be a non zero positive integer."<<endl;
        EXIT_FAILURE;

    }
    else if(k == 1)
    {
        return h_vertices.first_ring_points;
    }
    else if (k > 1){
        // number of ring = m+1
        for(int m = 1; m<k; m++) {
            if(m ==1 && k ==2){
                for(it = h_vertices.first_ring_points.begin(); it!=h_vertices.first_ring_points.end(); it++)
                {
                    int o = *it;
                    std::set<int>ringhood = selected_neighborhood(o);

                    for(std::set<int>::iterator iti = ringhood.begin(); iti != ringhood.end();iti++)
                    {
                        int j = *iti;

                        k_ringhood.insert(j);

                    }

                }
                return  k_ringhood;

            }
            if(m == 1)
            {
                for(it = h_vertices.first_ring_points.begin(); it!=h_vertices.first_ring_points.end(); it++)

                {
                    int o = *it;
                    std::set<int>ringhood = selected_neighborhood(o);
                    for(std::set<int>::iterator iti = ringhood.begin(); iti != ringhood.end();iti++)
                    {
                        int j = *iti;

                        k_ringhood.insert(j);

                    }

                }
            }
            else if(m>1)
            {

                final_ring = k_ringhood;
                for(ita = k_ringhood.begin(); ita!=k_ringhood.end(); ita++)

                {
                    int o = *ita;
                    tmp = selected_neighborhood(o);
                    for(itx = tmp.begin(); itx!=tmp.end(); itx++)
                    {
                        int l = *itx;
                        ringhood.insert(l);
                    }

                }

                for(std::set<int>::iterator iti = ringhood.begin(); iti != ringhood.end();iti++)
                {
                    int j = *iti;

                    final_ring.insert(j);

                }

                k_ringhood= final_ring;
            }

            if(m == k-1)
            {
                return final_ring;
            }
        }
    }



}

//void HarrisOperatorResponse::getNeighboorhood(int k_rings)
//{
//    int k, i;
//    //    set<int> neighbors;
//    std::set<int> neighbors;
//    std::set<int>::iterator it;
//    int pos, len_of_set;

//    // set all_first_neighbourhood lenghth to number of vertices
//    all_first_ring.resize(h_no_of_vertices);

//    //finding the first ring neighboorhood of all vertices:
//    for(k = 0; k < h_no_of_vertices; k++){
//        for(i = 0; i < h_no_of_faces; i++){
//            if((h_faces[i].v1 == k) || (h_faces[i].v2 == k) || (h_faces[i].v3 == k)){
//                neighbors.insert(h_faces[i].v1);
//                neighbors.insert(h_faces[i].v2);
//                neighbors.insert(h_faces[i].v3);
//            }
//        }

//        // to remove the vertex whose neighborhood was calculated
//        it=neighbors.begin();
//        neighbors.erase(it);

//        pos = 0;

////        int len_of_set = neighbors.size();

//        cout << neighbors.size()<< "  ";

//        all_first_ring[k].resize(len_of_set + 1);
//        all_first_ring[k][pos] = len_of_set; // storing the set length for each vertex in first index


//////        std::cout << endl << "Neighbors of vertex no " << k << ":";
////        for (it=neighbors.begin(); it!=neighbors.end(); ++it)
////            all_first_ring[k].push_back(*it);
//////            std::cout << ' ' << *it;
//////        std::cout << '\n';

////        std::cout << endl << "Neighbors of vertex no " << k << ":";

////        for(int x = 0; x <= len_of_set; x++)
////            std::cout << ' ' << all_first_ring[k][++pos];
////        std::cout << '\n';

//        neighbors.clear();

//    }
//}

    void HarrisOperatorResponse:: populate_data()
    {
        int n_vertex;
        int n_face;

        n_vertex = 0;
        n_face = 0;
        int a_face, b_face,c_face/*,d_face*/;
        float a_vert, b_vert,c_vert/*,d_vert*/;
        //    int temp;

        cout << endl << "-----------Start Harris------------" << endl ;
        cout << endl << "For Harris Detection" << endl;

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

        cout << endl << "--------------End Harris---------------" << endl;

    }

//   void HarrisOperatorResponse::display_interest_points()
//   {
//       int no_of_interest_points, point, pos;

//       //  to count no of vertices
//       cout << "Finding total number of vertices in Interest Point File" << endl;
//       while(h_inFile_int_points >> point)
//       {
//           no_of_interest_points++;
//       }
//       h_no_of_interest_points = no_of_interest_points;
//       cout << "No of Interest Points : " << h_no_of_interest_points << endl;

//       int_points = new int[no_of_interest_points];

//       std::ifstream h_inFile_int_points("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\interest_points.int");

//       pos = 0;
//       cout << "Populating Interest vertices:" << endl;
//       while(h_inFile_int_points >> point)
//       {
//           int_points[pos] = point;
//           pos++;
//       }

//       interest_vertices = int_points;

//   }
