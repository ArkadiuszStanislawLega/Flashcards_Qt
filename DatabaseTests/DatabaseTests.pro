QT += testlib
QT += sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../Database/dbmanager.cpp \
    ../Models/question.cpp \
    ../Models/tag.cpp \
    tst_databasetests.cpp

HEADERS += \
    ../Database/dbmanager.h \
    ../Models/question.h \
    ../Models/tag.h
