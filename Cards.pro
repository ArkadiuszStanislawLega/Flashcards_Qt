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
    Database/SqlGenerators/deletesql.cpp \
    Database/SqlGenerators/findbykeysql.cpp \
    Database/SqlGenerators/insertsql.cpp \
    Database/SqlGenerators/selectwithcriteriasql.cpp \
    Database/SqlGenerators/selectwithjoinsql.cpp \
    Database/SqlGenerators/updatesql.cpp \
    Database/SqlGenerators/wheresql.cpp \
    Database/SqlGenerators/selectsql.cpp \
    Database/SqlModels/questionmodelsql.cpp \
    Database/SqlModels/tagmodelsql.cpp \
    Database/SqlModels/tagandquestionrelationsql.cpp \
    Models/question.cpp \
    Models/tag.cpp \
    Views/learnview.cpp \
    Views/questionview.cpp \
    Views/relationview.cpp \
    Views/tagview.cpp \
    main.cpp \
    mainwindow.cpp \
    stringmanager.cpp

HEADERS += \
    Constants/strings.h \
    Constants/values.h \
    Converters/fromquerytoquestionconverter.h \
    Converters/fromquerytotagconverter.h \
    Converters/fromquerytovalueconverter.h \
    Database/dbmanager.h \
    Database/SqlGenerators/deletesql.h \
    Database/SqlGenerators/findbykeysql.h \
    Database/SqlGenerators/insertsql.h \
    Database/SqlGenerators/selectwithcriteriasql.h \
    Database/SqlGenerators/selectwithjoinsql.h \
    Database/SqlModels/questionmodelsql.h \
    Database/SqlModels/tagmodelsql.h \
    Database/SqlModels/tagandquestionrelationsql.h \
    Database/SqlGenerators/updatesql.h \
    Database/SqlGenerators/wheresql.h \
    Database/SqlGenerators/selectsql.h \
    Enums/StringID.h \
    Models/question.h \
    Models/tag.h \
    Views/learnview.h \
    Views/questionview.h \
    Views/relationview.h \
    Views/tagview.h \
    mainwindow.h \
    stringmanager.h

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
