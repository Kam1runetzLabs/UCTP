TARGET = model
TEMPLATE = lib
CONFIG += shared c++14 x86_64
QT += sql qml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers
DEPENDPATH  += ../helpers
LIBS += -L../lib -lhelper
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)
HEADERS += sqlobjects/timetableobject.h
HEADERS += timetable.h
SOURCES += timetable.cpp
HEADERS += sqlobjects/timeslotobject.h
HEADERS += timeslot.h
SOURCES += timeslot.cpp
HEADERS += sqlobjects/blockobject.h
HEADERS += block.h
SOURCES += block.cpp
HEADERS += sqlobjects/classroomobject.h
HEADERS += classroom.h
SOURCES += classroom.cpp
HEADERS += sqlobjects/groupobject.h
HEADERS += group.h
SOURCES += group.cpp
HEADERS += sqlobjects/teacherobject.h
HEADERS += teacher.h
SOURCES += teacher.cpp
HEADERS += sqlobjects/subjectobject.h
HEADERS += subject.h
SOURCES += subject.cpp