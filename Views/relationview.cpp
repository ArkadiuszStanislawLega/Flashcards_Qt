#include "relationview.h"

RelationView::RelationView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::RelationView)
{
    ui->setupUi(this);
    this->initialQuestionsListView();
    this->initialTagsComboBox();
}

void RelationView::initialQuestionsListView(){
    this->_questions_table_model = new QSqlRelationalTableModel;
    this->_questions_table_model->setTable(TABLE_QUESTIONS);
    this->_questions_table_model->select();

    this->ui->lv_questions->setModel(this->_questions_table_model);
    this->ui->lv_questions->setModelColumn(this->_questions_table_model->record().indexOf(COLUMN_VALUE));
}

void RelationView::initialTagsComboBox(){
    this->_tags_combo_box_model = new QSqlRelationalTableModel;
    this->_tags_combo_box_model->setTable(TABLE_TAGS);
    this->_tags_combo_box_model->select();

    this->ui->comboBox->setModel(this->_tags_combo_box_model);
    this->ui->comboBox->setModelColumn(this->_tags_combo_box_model->record().indexOf(COLUMN_TAG));
}



