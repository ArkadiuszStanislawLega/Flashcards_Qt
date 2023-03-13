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
    Models/model.cpp \
    Models/question.cpp \
    Models/tag.cpp \
    Views/learnview.cpp \
    Views/questionview.cpp \
    Views/relationview.cpp \
    Views/tagview.cpp \
    Views/view.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Constants/strings.h \
    Constants/values.h \
    Controllers/controller.h \
    Database/crud.h \
    Database/dbmanager.h \
    Database/manytomany.h \
    Models/model.h \
    Models/question.h \
    Models/tag.h \
    Views/learnview.h \
    Views/questionview.h \
    Views/relationview.h \
    Views/tagview.h \
    Views/view.h \
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
