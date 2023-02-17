#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Models/model.h"
#include "Models/question.h"
#include "Database/dbquestion.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_b_get_tag_clicked();

    void on_b_add_question_clicked();

    void on_b_remove_question_clicked();

    void on_b_update_question_clicked();

private:
    Ui::MainWindow *ui;
    Model *_model;
    Question *_selected_question;

};
#endif // MAINWINDOW_H
