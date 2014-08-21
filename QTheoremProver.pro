#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T09:40:23
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTheoremProver
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    QProofModel.cpp \
    QRememberPositionLineEdit.cpp

HEADERS  += MainWindow.hpp \
    QProofModel.hpp \
    QRememberPositionLineEdit.hpp

FORMS    += MainWindow.ui
CONFIG += C++11
INCLUDEPATH += ../
