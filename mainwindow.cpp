#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->_model = new Model();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_b_get_tag_clicked()
{
    Question *q = new Question();
    q->set_answer("Cost tam");
    q->set_value("Value val");
    if(DbQuestion::isCreate(q)){
            Question *q1 = DbQuestion::read(1);
            qDebug() << q1->to_string();
            this->_model->ReadTag();
        ui->l_output->setText(q1->to_string());
    }
}

