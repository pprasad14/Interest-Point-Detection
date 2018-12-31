#ifndef HARRISOPERATORRESPONSE_H
#define HARRISOPERATORRESPONSE_H

struct Harris_vertices {
    float x;
    float y;
    float z;
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

    Harris_faces * h_faces;
    Harris_vertices * h_vertices;

//    void populate_data(Harris_faces* f, Harris_vertices* v, int f_len, int v_len);
    void populate_data();

    void getNeighboorhood(int k_rings);


    HarrisOperatorResponse();

    ~HarrisOperatorResponse();
};

#endif // HARRISOPERATORRESPONSE_H
