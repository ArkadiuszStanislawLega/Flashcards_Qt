#include "questionview.h"

void QuestionView::initialQuestionsListView(){
    int column_value_index;
    this->_table_model = new QSqlTableModel;
    this->_table_model->setTable(TABLE_QUESTIONS);
    this->_table_model->select();
    column_value_index = this->_table_model->record().indexOf(COLUMN_VALUE);

    ui->lv_created_quesions->setModel(this->_table_model);
    ui->lv_created_quesions->setModelColumn(column_value_index);
}


QuestionView::QuestionView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::QuestionView)
{
    ui->setupUi(this);
    this->initialQuestionsListView();
}

void QuestionView::on_b_create_question_clicked()
{
    Question *q = new Question();
    q->set_answer(ui->te_answer->toPlainText());
    q->set_value(ui->te_value->toPlainText());

    DbQuestion::isCreate(q);
    this->_table_model->select();
}

void QuestionView::on_b_update_question_clicked()
{

}

void QuestionView::on_b_remove_question_clicked()
{

}


