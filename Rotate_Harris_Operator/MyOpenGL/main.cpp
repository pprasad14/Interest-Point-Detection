
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
    cout << "Main: creating Harris Object: " << endl;
    HarrisOperatorResponse h_obj;

    h_obj.populate_data();
    cout << endl << "Main: Harris: populating vertices and faces done!" << endl;

    h_obj.getNeighboorhood();
    cout << endl << "Main: getting 1st ring neighborhood of all vertices done!" << endl;

//    std::set<int> ring_k = h_obj.get_k_ringhood(h_obj.h_vertices[500],4);

//    std::string output_loc;
//    output_loc = "C:\\Users\\Prem Prasad\\Desktop\\MAIA Projects\\Software Engineering\\OFF files\\Apple.ini.txt";

//    std::ofstream outFile(output_loc);

//    if(outFile)
//    {
//        cout << endl << "Main: Output file create at location: " << output_loc << endl;
//        std::set<int>::iterator it;
//        for(it = ring_k.begin();it!= ring_k.end();it++)
//        {
//            int val = *it;
//            outFile << val <<" ";
//        }
//    }
//    else{
//        cout << endl << "Main: ERROR, CANNOT CREATE THE FILE! " << endl;
//    }

//    outFile.close();

    cout << "Main: displaying output:" << endl << endl;

    cout << endl << "Main: Start of computing Harris Response:" << endl;
    h_obj.compute_harris_response(3,3,0.4);

    cout << endl << "Main: Start of computing Candidate Interest Points:"<< endl;
    h_obj.compute_canditate_interest_points();

    cout << endl << "Main: Start of computing Interest Points from Candidate Interest Points" << endl;
    h_obj.compute_interest_points(100);

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
