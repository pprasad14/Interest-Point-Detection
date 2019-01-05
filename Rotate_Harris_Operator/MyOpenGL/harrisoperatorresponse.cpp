
#include "harrisoperatorresponse.h"

#include <QtOpenGL>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <set>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cfloat>


#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>


std::string h_line;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

std::string file_path_vert = "C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.vert";
std::string file_path_tri = "C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.tri";

std::ifstream h_inFile_vert(file_path_vert);
std::ifstream h_inFile_face(file_path_tri);

//std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.vert");
//std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.tri");

//std::ifstream h_inFile_int_points("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\Apple.ini.txt");


//std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.vert");
//std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\octahedron.tri");


HarrisOperatorResponse::HarrisOperatorResponse()
{
    cout << endl << "Constructor: Harris: Populating Data:" << endl;
}

HarrisOperatorResponse::~HarrisOperatorResponse()
{

}

void HarrisOperatorResponse::getNeighboorhood()
{
    int k, i;

    //finding the first ring neighboorhood of all vertices:
    for(k = 0; k < h_no_of_vertices; k++){
        for(i = 0; i < h_no_of_faces; i++){
            if((h_faces[i].v1 == k) || (h_faces[i].v2 == k) || (h_faces[i].v3 == k)){
                h_vertices[k].first_ring_points.insert(h_faces[i].v1);
                h_vertices[k].first_ring_points.insert(h_faces[i].v2);
                h_vertices[k].first_ring_points.insert(h_faces[i].v3);
            }
        }
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

    std::ifstream h_inFile_vert(file_path_vert);
    std::ifstream h_inFile_face(file_path_tri);

//    std::ifstream h_inFile_vert("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.vert");
//    std::ifstream h_inFile_face("C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\tri_vert\\Apple.tri");

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


void HarrisOperatorResponse::compute_harris_response( int rings, int rings_max, float H)
{
    for(int c = 0; c < h_no_of_vertices ; c++)
    {
        float x_center = 0, y_center = 0, z_center = 0;
        float x_center_trans = 0, y_center_trans = 0, z_center_trans = 0;

        int counter = 0;

        // Calculating the neighborhood for the vertex
        std::set<int> temp_k_neighborhood = get_k_ringhood(h_vertices[c], rings);



        cout << endl << "start of Harris response for vertex " << c << " : " << endl;
        // new stuct variable for storing the neighborhood as a separate object
        new_vertices = new Harris_vertices[temp_k_neighborhood.size()];

        //array to hold the indexes of the neighborhood vertices
        int neighborhood_array[temp_k_neighborhood.size()];

        //filling the array:
        for(std::set<int>::iterator it = temp_k_neighborhood.begin(); it != temp_k_neighborhood.end(); it++)
        {
            int val = *it;
            neighborhood_array[counter++] = val;
        }


        cout << endl << "Array Values:" ;
        for(int k = 0; k < temp_k_neighborhood.size(); k++)
            cout << " " << neighborhood_array[k];
        cout << endl;

        counter = 0;
        //populating the new_vertices with the x,y,z of the neighborhood points
        for(int i = 0; i< temp_k_neighborhood.size(); i++)
        {
            new_vertices[i].x = h_vertices[neighborhood_array[i]].x;
            new_vertices[i].y = h_vertices[neighborhood_array[i]].y;
            new_vertices[i].z = h_vertices[neighborhood_array[i]].z;

        }

        //Centroid calcualation for Original Neighbourhood:
        for(std::set<int>::iterator iti = temp_k_neighborhood.begin(); iti != temp_k_neighborhood.end(); iti++)
        {
            int j = *iti;

            x_center = x_center + h_vertices[j].x;
            y_center = y_center + h_vertices[j].y;
            z_center = z_center + h_vertices[j].z;

        }

        x_center = x_center/temp_k_neighborhood.size();
        y_center = y_center/temp_k_neighborhood.size();
        z_center = z_center/temp_k_neighborhood.size();

        cout << " Original centroid coordinates: " ;
        cout << " x: " << x_center << " y: " << y_center << " z: " << z_center  << " size: " << temp_k_neighborhood.size() << endl;



        //translating the new_vertices points to origin:
        for(int i = 0; i < temp_k_neighborhood.size(); i++)
        {
            new_vertices[i].x = new_vertices[i].x - x_center ;
            new_vertices[i].y = new_vertices[i].y - y_center ;
            new_vertices[i].z = new_vertices[i].z - z_center ;
        }


        //testing the center of the translated points:
        for(int j = 0; j < temp_k_neighborhood.size(); j++)
        {
            x_center_trans = x_center_trans + new_vertices[j].x;
            y_center_trans = y_center_trans + new_vertices[j].y;
            z_center_trans = z_center_trans + new_vertices[j].z;

        }

        x_center_trans = x_center_trans/temp_k_neighborhood.size();
        y_center_trans = y_center_trans/temp_k_neighborhood.size();
        z_center_trans = z_center_trans/temp_k_neighborhood.size();

        cout << endl << "Translated centroid coordinates (should be near 0)" ;
        cout << " x:" << x_center_trans << " y: " << y_center_trans << " z: " << z_center_trans  << " size: " << temp_k_neighborhood.size() << endl;


        //Compute Covariance Matrix
        double A[9];
        for (register int i=0; i<9; i++)
            A[i]=0;
        for(register int i=0; i<temp_k_neighborhood.size(); i++)
        {
            float x = new_vertices[i].x;
            float y = new_vertices[i].y;
            float z = new_vertices[i].z;

            A[0] += x*x;	   A[1] += x*y;	   A[2] += x*z;
            A[4] += y*y;	   A[5] += y*z;
            A[8] += z*z;
        }
        A[3]=A[1];	A[6]=A[2];	A[7]=A[5];


        // Calculate PCA using Covariance Martix (A)
        gsl_matrix_view m = gsl_matrix_view_array(A, 3, 3);
        gsl_vector* eval = gsl_vector_alloc(3);
        gsl_matrix* evec = gsl_matrix_alloc(3, 3);

        gsl_eigen_symmv_workspace* w = gsl_eigen_symmv_alloc(3);
        gsl_eigen_symmv(&m.matrix, eval, evec, w);
        gsl_eigen_symmv_free(w);


        // Order Eigenvectors decreasingly by Eigenvalues
        gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_DESC);


        // Export components of the New Coordinate System
        double x_1 = gsl_matrix_get(evec, 0, 0);	double x_2 = gsl_matrix_get(evec, 1, 0); double x_3 = gsl_matrix_get(evec, 2, 0);
        double y_1 = gsl_matrix_get(evec, 0, 1);	double y_2 = gsl_matrix_get(evec, 1, 1); double y_3 = gsl_matrix_get(evec, 2, 1);
        double z_1 = gsl_matrix_get(evec, 0, 2);	double z_2 = gsl_matrix_get(evec, 1, 2); double z_3 = gsl_matrix_get(evec, 2, 2);


        //Plane-Fitting
        double x2 = new_vertices[0].x - x_center;
        double y2 = new_vertices[0].y - y_center;
        double z2 = new_vertices[0].z - z_center;


        if((z_1*x2 + z_2*y2 + z_3*z2) < 0){
            z_1 = -z_1;
            z_2 = -z_2;
            z_3 = -z_3;

            double aux_x1 = x_1;
            double aux_x2 = x_2;
            double aux_x3 = x_3;

            x_1 = y_1;
            x_2 = y_2;
            x_3 = y_3;
            y_1 = aux_x1;
            y_2 = aux_x2;
            y_3 = aux_x3;
        }


        // Rotation using New Coordinate System
        for(register int i=0; i<temp_k_neighborhood.size(); i++)
        {
            double x = new_vertices[i].x;
            double y = new_vertices[i].y;
            double z = new_vertices[i].z;

            new_vertices[i].x = x_1*x + x_2*y + x_3*z;
            new_vertices[i].y = y_1*x + y_2*y + y_3*z;
            new_vertices[i].z = z_1*x + z_2*y + z_3*z;
        }


        // Shift all the points so that the Point of Analysis is at the Origin
        // of the XY plane. We only move in the X and Y coordinates.

        double x = new_vertices[0].x;
        double y = new_vertices[0].y;

        for(register int i=0; i<temp_k_neighborhood.size(); i++)
        {
            new_vertices[i].x = new_vertices[i].x - x;
            new_vertices[i].y = new_vertices[i].y - y;
        }

        double C[36];
        for (register int i=0; i<36; i++)
            C[i]=0;
        double D[6];
        for (register int i=0; i<6; i++)
            D[i]=0;


        for(register int i=0; i<temp_k_neighborhood.size(); i++)
        {
            double x = new_vertices[i].x;
            double y = new_vertices[i].y;
            double z = new_vertices[i].z;

            double x2 = x*x;
            double y2 = y*y;
            double x3 = x2*x;
            double y3 = y2*y;

            C[0]  += x*x3;	C[1]  += x3*y;	C[2]  += x2*y2;	C[3] += x3;		C[4] += x2*y;	C[5] += x2;
            C[7]  += x2*y2;	C[8]  += x*y3;	C[9]  += x2*y;	C[10] += x*y2;	C[11] += x*y;
            C[14] += y*y3;	C[15] += x*y2;	C[16] += y3;	C[17] += y2;
            C[21] += x2;	C[22] += x*y;	C[23] += x;
            C[28] += y2;	C[29] += y;
            D[0]  += z*x2;	D[1]  += z*x*y;	D[2]  += z*y2;	D[3] += z*x;	D[4] += z*y;	D[5] += z;
        }

        C[6]  = C[1];
        C[12] = C[2];	C[13] = C[8];
        C[18] = C[3];	C[19] = C[9];	C[20] = C[15];
        C[24] = C[4];	C[25] = C[10];	C[26] = C[16];	C[27] = C[22];
        C[30] = C[5];	C[31] = C[11];	C[32] = C[17];	C[33] = C[23];	C[34] = C[29];

        C[35] = (double)temp_k_neighborhood.size();


        //Solve Linear Systems using GSL
        gsl_matrix_view m1 = gsl_matrix_view_array(C, 6, 6);
        gsl_vector_view b1 = gsl_vector_view_array(D, 6);
        gsl_vector *x1 = gsl_vector_alloc(6);

        int s1;

        gsl_permutation *p11 = gsl_permutation_alloc(6);
        gsl_linalg_LU_decomp(&m1.matrix, p11, &s1);
        gsl_linalg_LU_solve(&m1.matrix, p11, &b1.vector, x1);

        //Extract Solution of Quadratic Surface
        double c20_2 = gsl_vector_get(x1, 0);
        double c11 = gsl_vector_get(x1, 1);
        double c02_2 = gsl_vector_get(x1, 2);
        double c10 = gsl_vector_get(x1, 3);
        double c01 = gsl_vector_get(x1, 4);
        double c0 = gsl_vector_get(x1, 5);

        double c20 = c20_2*2;
        double c02 = c02_2*2;

        double fx2 = c10*c10 + 2*c20*c20 + 2*c11*c11;   //A
        double fy2  = c10*c10 + 2*c11*c11 + 2*c02*c02;  //B
        double fxfy = c10*c01 + 2*c20*c11 + 2*c11*c02;  //C


        //Calculate Harris Response
        long double resp = fx2*fy2 - fxfy*fxfy - H*(fx2 + fy2)*(fx2 + fy2);

        h_vertices[c].Harris_response = resp;
        std::cout<<"Response of vertex "<<c<<": "<<resp<<endl;

        if(resp > H_max)
            H_max = resp;

        gsl_vector_free(x1);
        gsl_vector_free(eval);
        gsl_matrix_free(evec);
        gsl_permutation_free(p11);


        temp_k_neighborhood.clear();

        delete[] new_vertices;

        //        cout << "End of Harris response for vertex " << c << " : " << endl;
    }


}
