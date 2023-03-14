#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->quesiton_view,&QuestionView::added_question_to_db,ui->relation_view,&RelationView::added_question_to_db);
    QObject::connect(ui->tag_view,&TagView::added_tag_to_db,ui->relation_view,&RelationView::added_tag_to_db);

    setWindowTitle("Cards");
}

MainWindow::~MainWindow()
{
    delete ui;
}
