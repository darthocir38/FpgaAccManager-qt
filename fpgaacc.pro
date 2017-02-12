#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T20:13:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fpgaacc
TEMPLATE = app

SOURCES   += $$system("find . '(' -name '*.cpp' -or -name '*.cc'  ')' -not -name '*.git*' -not -wholename './libs/*' -not -wholename '*/.build*'")
HEADERS   += $$system("find . '(' -name '*.h'   -or -name '*.hpp' ')' -not -name '*.git*' -not -wholename './libs/*' -not -wholename '*/.build*'")
FORMS     += $$system("find . -name '*.ui'                            -not -name '*.git*' -not -wholename './libs/*' -not -wholename '*/.build*'")
RESOURCES += $$system("find . -name '*.qrc'                           -not -name '*.git*' -not -wholename './libs/*' -not -wholename '*/.build*'")

