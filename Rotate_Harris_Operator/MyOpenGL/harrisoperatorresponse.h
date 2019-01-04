#ifndef HARRISOPERATORRESPONSE_H
#define HARRISOPERATORRESPONSE_H

#include<iostream>
#include<vector>
#include<set>

struct Harris_vertices {
    float x;
    float y;
    float z;
    std::set<int> first_ring_points;
};

struct Harris_faces {
    int v1;
    int v2;
    int v3;
};

class HarrisOperatorResponse
{
public:

    int h_no_of_faces;
    int h_no_of_vertices;
    int h_no_of_rings;
//    int h_no_of_interest_points;

    Harris_faces * h_faces;
    Harris_vertices * h_vertices;

    HarrisOperatorResponse();

    std::set<int> selected_neighborhood(int index);

    void display_ringhood(std::set<int> ringhood);
    std::set<int> get_k_ringhood(Harris_vertices vertex, int k);

    void populate_data();
    void getNeighboorhood();

    ~HarrisOperatorResponse();

//    std::vector< std::vector <int> > all_first_ring;

//    int interest_vertices[];

//    void populate_data(Harris_faces* f, Harris_vertices* v, int f_len, int v_len);
//    void populate_data();
//    void getNeighboorhood();

//    void display_interest_points();

};

#endif // HARRISOPERATORRESPONSE_H
