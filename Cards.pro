QT       += core gui
QT  += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Converters/fromquerytoquestionconverter.cpp \
    Converters/fromquerytotagconverter.cpp \
    Converters/fromquerytovalueconverter.cpp \
    Database/dbmanager.cpp \
    Database/deletesql.cpp \
    Database/findbykeysql.cpp \
    Database/insertsql.cpp \
    Database/questionmodelsql.cpp \
    Database/selectsql.cpp \
    Database/selectwithcriteriasql.cpp \
    Database/selectwithjoinsql.cpp \
    Database/tagandquestionrelationsql.cpp \
    Database/tagmodelsql.cpp \
    Database/updatesql.cpp \
    Database/wheresql.cpp \
    Models/question.cpp \
    Models/tag.cpp \
    Views/learnview.cpp \
    Views/questionview.cpp \
    Views/relationview.cpp \
    Views/tagview.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Constants/strings.h \
    Constants/values.h \
    Converters/fromquerytoquestionconverter.h \
    Converters/fromquerytotagconverter.h \
    Converters/fromquerytovalueconverter.h \
    Database/crud.h \
    Database/dbmanager.h \
    Database/deletesql.h \
    Database/findbykeysql.h \
    Database/insertsql.h \
    Database/manytomany.h \
    Database/questionmodelsql.h \
    Database/selectsql.h \
    Database/selectwithcriteriasql.h \
    Database/selectwithjoinsql.h \
    Database/tagandquestionrelationsql.h \
    Database/tagmodelsql.h \
    Database/updatesql.h \
    Database/wheresql.h \
    Models/question.h \
    Models/tag.h \
    Views/learnview.h \
    Views/questionview.h \
    Views/relationview.h \
    Views/tagview.h \
    mainwindow.h

FORMS += \
    Views/learnview.ui \
    Views/questionview.ui \
    Views/relationview.ui \
    Views/tagview.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    fiszka.db
