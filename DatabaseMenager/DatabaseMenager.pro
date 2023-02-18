QT += testlib
QT += sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_databasemanager.cpp \
    ../Database/dbmanager.cpp \
    ../Database/dbquestion.cpp \
    ../Models/model.cpp \
    ../Models/question.cpp \
    ../Models/tag.cpp

HEADERS += \
    ../Database/dbmanager.h \
    ../Database/dbquestion.h \
    ../Models/model.h \
    ../Models/question.h \
    ../Models/tag.h
