#include "tagview.h"

TagView::TagView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::TagView)
{
    ui->setupUi(this);
    this->_selected_tag = nullptr;
    this->initialTagsListView();
}

void TagView::printInfo(const QString &value, bool isError){
   QPalette pal =this->ui->l_info->palette();
   pal.setColor(QPalette::Window, QColor(isError ? Qt::red : Qt::transparent));

   this->ui->l_info->setText(value);
   this->ui->l_info->setPalette(pal);
}

void TagView::cleanTextEditors(){
    this->ui->te_create_tag->clear();
}

void TagView::initialTagsListView(){
    this->_table_model = new QSqlRelationalTableModel;
    this->_table_model->setTable(TABLE_TAGS);
    this->_table_model->select();

    this->ui->lv_created_tags->setModel(this->_table_model);
    this->ui->lv_created_tags->setModelColumn(this->_table_model->record().indexOf(COLUMN_TAG));
}

void TagView::on_b_create_tag_clicked()
{
    if(ui->te_create_tag->toPlainText() == ""){
        this->printInfo(FIELD_TAG_CANT_EMPTY, true);
        return;
    }

    Tag *tag = new Tag(this);
    tag->set_tag(ui->te_create_tag->toPlainText());

    if(tag->isCreate()){
       this->printInfo(TAG_CREATED_CORRECTLY);
    } else {
       this->printInfo(DATABASE_ERROR, true);
    }

    this->_table_model->select();
    this->cleanTextEditors();

    emit added_tag_to_db();
    delete tag;
}

void TagView::on_b_update_tag_clicked()
{
    if(this->ui->te_create_tag->toPlainText() == ""){
        this->printInfo(FIELD_TAG_CANT_EMPTY, true);
        return;
    }

    if(this->_selected_tag == nullptr){
        this->printInfo(SELECT_TAG_FIRST, true);
        return;
    }

    this->_selected_tag->set_tag(ui->te_create_tag->toPlainText());

    if(this->_selected_tag->isUpdate()){
        this->_table_model->select();
        this->printInfo(TAG_UPDATE_SUCCESFULLY);
    } else {
        this->printInfo(DATABASE_ERROR, true);
    }

    this->cleanTextEditors();
    emit updated_tag_from_db();
}

void TagView::on_b_remove_tag_clicked()
{
    if(this->_selected_tag == nullptr){
        this->printInfo(SELECT_TAG_FIRST, true);
        return;
    }

    if(this->_selected_tag->isRemoved()){
        this->_table_model->select();
        this->_selected_tag = nullptr;
        this->printInfo(TAG_SUCCESFULLY_REMOVED);
    } else {
        this->printInfo(DATABASE_ERROR, true);
    }

    this->cleanTextEditors();

    emit remove_tag_from_db();
}

void TagView::on_lv_created_tags_clicked(const QModelIndex &index)
{
   int id, id_column_index, tag_column_index;
   QString tag;

   id_column_index = this->_table_model->record().indexOf(COLUMN_ID);
   tag_column_index = this->_table_model->record().indexOf(COLUMN_TAG);

   id = this->_table_model->index(index.row(), id_column_index).data(Qt::DisplayRole).toInt();
   tag = this->_table_model->index(index.row(), tag_column_index).data(Qt::DisplayRole).toString();

   this->_selected_tag = new Tag(id, tag, this);

   this->ui->te_create_tag->setText(tag);
}
