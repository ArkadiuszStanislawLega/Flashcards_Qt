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

void MainWindow::on_b_add_question_clicked()
{
   Question *q = new Question();
   q->set_value(ui->te_question_value->toPlainText());
   q->set_answer(ui->te_question_answer->toPlainText());
   if(DbQuestion::isCreate(q)){
       Question *qa = DbQuestion::read(DbQuestion::findId(q->get_value(), q->get_answer()));
       ui->l_output->setText(qa->to_string());
   }
}

