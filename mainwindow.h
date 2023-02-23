#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Models/model.h"
#include "Models/question.h"
#include "Database/dbquestion.h"
#include "Database/dbtag.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Model *_model;
    Question *_selected_question;
    Tag *_selected_tag;
};
#endif // MAINWINDOW_H
