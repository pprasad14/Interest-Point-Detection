QT += core
QT -= gui

CONFIG += c++11

TARGET = test_console
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    HarrisDetector.cpp \
    Mesh.cpp \
    Properties.cpp \
    util.cpp \
    Vertex.cpp

HEADERS += \
    Clock.h \
    Distance.h \
    Face.h \
    HarrisDetector.h \
    Mesh.h \
    Properties.h \
    util.h \
    Vertex.h


