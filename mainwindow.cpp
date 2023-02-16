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
    this->_model->ReadTag();
}

