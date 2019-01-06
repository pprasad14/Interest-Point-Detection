
// main.cpp

#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include <fstream>
#include <set>

#include "window.h"
#include "harrisoperatorresponse.h"

using std::cout;
using std::endl;
using std::cin;
using std::cerr;


int main(int argc, char *argv[])
{
    int /*zoom*/ how_many_rings=0;
    float what_fraction=0;
    cout << endl << "----------Harris Interest Point Detection-----------------" << endl;
//    cout << endl << "Enter zoom to be considered: " ;
//    cin >> zoom;
    cout << endl << "Enter Rings to be Considered: ";
    cin >> how_many_rings;
    cout << "Enter fraction of Candidates to take: ";
    cin >> what_fraction;


    cout << "Main: creating Harris Object: " << endl;
    HarrisOperatorResponse h_obj;

    h_obj.populate_data();
    cout << endl << "Main: Harris: populating vertices and faces done!" << endl;

    h_obj.getNeighboorhood();
    cout << endl << "Main: getting 1st ring neighborhood of all vertices done!" << endl;


    cout << "Main: displaying output:" << endl << endl;

    cout << endl << "Main: Start of computing Harris Response:" << endl;
    h_obj.compute_harris_response(how_many_rings); // k ring

    cout << endl << "Main: Start of computing Candidate Interest Points:"<< endl;
    h_obj.compute_canditate_interest_points();

    cout << endl << "Main: Start of computing Interest Points from Candidate Interest Points" << endl;
    h_obj.compute_interest_points(what_fraction);

    cout << endl << "End of computing Harris Response:" << endl;


    QApplication app(argc, argv);

    Window window;
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();


    window.setWindowTitle("OpenGL with Qt");

    cout << endl << "hello" << endl;


    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    return app.exec();



}
