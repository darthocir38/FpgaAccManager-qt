#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T20:13:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fpgaacc
TEMPLATE = app


SOURCES += main.cpp\
        fpgaacc.cpp \
    generategriddialog.cpp \
    editgriddialog.cpp

HEADERS  += fpgaacc.h \
    generategriddialog.h \
    editgriddialog.h

FORMS    += fpgaacc.ui \
    generategriddialog.ui \
    editgriddialog.ui
