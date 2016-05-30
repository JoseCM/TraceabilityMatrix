#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T10:43:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TraceabilityMatrix
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    documentview.cpp \
    checkboxdelegate.cpp \
    traceabilityview.cpp \
    documenteditorview.cpp

HEADERS  += mainwindow.h \
    documentview.h \
    checkboxdelegate.h \
    traceabilityview.h \
    documenteditorview.h

FORMS    += mainwindow.ui \
    documentview.ui \
    traceabilityview.ui \
    documenteditorview.ui
