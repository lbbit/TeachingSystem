#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T16:32:24
#
#-------------------------------------------------

QT       += core gui
QT      +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeachingSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwidget.cpp \
    loginwidget.cpp \
    dbconnection.cpp \
    adminwidget.cpp \
    adminteawidget.cpp \
    adminstuwidget.cpp \
    admincouwidget.cpp \
    studentwidget.cpp \
    stuscorewidget.cpp \
    stucouwidget.cpp \
    stupasswidget.cpp \
    teacherwidget.cpp \
    teascorewidget.cpp \
    teapasswidget.cpp

HEADERS  += mainwidget.h \
    loginwidget.h \
    dbconnection.h \
    adminwidget.h \
    adminteawidget.h \
    adminstuwidget.h \
    admincouwidget.h \
    studentwidget.h \
    stuscorewidget.h \
    stucouwidget.h \
    stupasswidget.h \
    teacherwidget.h \
    teascorewidget.h \
    teapasswidget.h
