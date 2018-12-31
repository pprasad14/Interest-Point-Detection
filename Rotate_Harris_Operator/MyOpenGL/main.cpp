// main.cpp

#include <QApplication>
#include <QDesktopWidget>
#include<iostream>

#include "window.h"
#include "harrisoperatorresponse.h"

using std::cout;
using std::endl;
using std::cin;
using std::cerr;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window window;
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();


    HarrisOperatorResponse h_obj;

    window.setWindowTitle("OpenGL with Qt");

    cout << endl << "hello" << endl;


    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    return app.exec();



}
