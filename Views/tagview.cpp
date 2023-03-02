#include "tagview.h"

TagView::TagView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::TagView)
{
    ui->setupUi(this);
    this->_selected_tag = nullptr;
}

void TagView::initialTagsListView(){
    int tag_index_column;
    this->_table_model = new QSqlRelationalTableModel;
    this->_table_model->setTable(TABLE_TAGS);
    this->_table_model->select();
    this->_table_model->setRelation(this->_table_model->fieldIndex(TABLE_TAGS), QSqlRelation(TABLE_TAGS, COLUMN_ID, COLUMN_TAG));
    tag_index_column = this->_table_model->record().indexOf(COLUMN_TAG);

    this->ui->lv_created_tags->setModel(this->_table_model);
    this->ui->lv_created_tags->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->lv_created_tags->setModelColumn(tag_index_column);
}

void TagView::on_b_create_tag_clicked()
{

}

void TagView::on_b_update_tag_clicked()
{

}

void TagView::on_b_remove_tag_clicked()
{

}

