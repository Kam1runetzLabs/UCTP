TARGET = controller
TEMPLATE = lib
CONFIG += shared c++14 x86_64
QT += network sql xml qml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers ../models
DEPENDPATH  += ../helpers ../models
LIBS += -L../lib -lhelper -lmodel
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)

HEADERS += applicationcontroller.h
SOURCES += applicationcontroller.cpp
HEADERS += timetablecontroller.h
SOURCES += timetablecontroller.cpp
HEADERS += timeslotcontroller.h
SOURCES += timeslotcontroller.cpp
HEADERS += blockcontroller.h
SOURCES += blockcontroller.cpp
HEADERS += classroomcontroller.h
SOURCES += classroomcontroller.cpp
HEADERS += groupcontroller.h
SOURCES += groupcontroller.cpp
HEADERS += teachercontroller.h
SOURCES += teachercontroller.cpp
HEADERS += subjectcontroller.h
SOURCES += subjectcontroller.cpp
