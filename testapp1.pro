#-------------------------------------------------
#
# Project created by QtCreator 2016-02-06T17:36:55
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testapp1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    news.cpp \
    utility.cpp

HEADERS  += mainwindow.h \
    news.h \
    utility.h

FORMS    += mainwindow.ui
