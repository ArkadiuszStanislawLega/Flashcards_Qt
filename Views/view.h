#ifndef VIEW_H
#define VIEW_H

#include "../Models/model.h"
#include "mainwindow.h"

#include <QApplication>

class View
{
private:
    Model *_model;
    QApplication *_parent;
    MainWindow _main_window;
public:
    View(Model *, QApplication *);
    void show_app();
};

#endif // VIEW_H
