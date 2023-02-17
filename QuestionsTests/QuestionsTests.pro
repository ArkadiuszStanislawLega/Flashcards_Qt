QT += testlib
QT += sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_questionstests.cpp \
    ../Database/dbmanager.cpp \
    ../Database/dbquestion.cpp \
    ../Models/question.cpp \
    ../Models/tag.cpp

HEADERS += \
    ../Constants/strings.h \
    ../Database/dbmanager.h \
    ../Database/dbquestion.h \
    ../Models/question.h \
    ../Models/tag.h
