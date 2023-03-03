#include "relationview.h"

RelationView::RelationView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::RelationView)
{
    ui->setupUi(this);
    this->initialQuestionsListView();
}

void RelationView::initialQuestionsListView(){
    this->_questions_table_model = new QSqlRelationalTableModel;
    this->_questions_table_model->setTable(TABLE_QUESTIONS);
    this->_questions_table_model->select();

    this->ui->lv_questions->setModel(this->_questions_table_model);
    this->ui->lv_questions->setModelColumn(this->_questions_table_model->record().indexOf(COLUMN_VALUE));
}
