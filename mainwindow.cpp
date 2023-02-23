#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Cards");
    this->_model = new Model();
    this->_selected_question = nullptr;
    this->_selected_tag = nullptr;
    QLabel *l = findChild<QLabel*>("l_output");
    l->setText("dstalem sie");
}

MainWindow::~MainWindow()
{
    delete ui;
}
