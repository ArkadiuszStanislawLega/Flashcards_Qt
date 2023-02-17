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
       this->_selected_question = DbQuestion::read(DbQuestion::findId(q->get_value(), q->get_answer()));
       ui->l_output->setText(this->_selected_question->to_string());
   }
}


void MainWindow::on_b_remove_question_clicked()
{
    if(this->_selected_question != nullptr){
       if (DbQuestion::isRemoved(this->_selected_question->get_id())){
           this->_selected_question = nullptr;
           ui->l_output->setText("Skasowano");
       }
    }
}

void MainWindow::on_b_update_question_clicked()
{
    this->_selected_question->set_answer(ui->te_question_answer->toPlainText());
    this->_selected_question->set_value(ui->te_question_value->toPlainText());
    if(DbQuestion::isUpdate(this->_selected_question)){
        this->_selected_question = DbQuestion::read(this->_selected_question->get_id());
        ui->l_output->setText(this->_selected_question->to_string());
    }
}

