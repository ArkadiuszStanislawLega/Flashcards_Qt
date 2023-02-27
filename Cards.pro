QT       += core gui
QT  += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/controller.cpp \
    Database/dbmanager.cpp \
    Database/dbquestion.cpp \
    Database/dbrelationquestiontag.cpp \
    Database/dbtag.cpp \
    Models/model.cpp \
    Models/question.cpp \
    Models/tag.cpp \
    Views/questionview.cpp \
    Views/view.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Constants/strings.h \
    Constants/values.h \
    Controllers/controller.h \
    Database/dbmanager.h \
    Database/dbquestion.h \
    Database/dbrelationquestiontag.h \
    Database/dbtag.h \
    Models/model.h \
    Models/question.h \
    Models/tag.h \
    Views/questionview.h \
    Views/view.h \
    mainwindow.h

FORMS += \
    Views/questionview.ui \
    Views/tagview.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    fiszka.db
