#include "tagview.h"

TagView::TagView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::TagView)
{
    ui->setupUi(this);
    this->_selected_tag = nullptr;
    this->initialTagsListView();
}

void TagView::printInfo(const QString &value, bool isError=false){
   QPalette pal =this->ui->l_info->palette();
   pal.setColor(QPalette::Window, QColor(isError ? Qt::red : Qt::transparent));

   this->ui->l_info->setText(value);
   this->ui->l_info->setPalette(pal);
}

void TagView::initialTagsListView(){
    int tag_index_column;

    this->_table_model = new QSqlRelationalTableModel;
    this->_table_model->setTable(TABLE_TAGS);
    this->_table_model->select();

    tag_index_column = this->_table_model->record().indexOf(COLUMN_TAG);

    this->ui->lv_created_tags->setModel(this->_table_model);
    this->ui->lv_created_tags->setModelColumn(tag_index_column);
}

void TagView::on_b_create_tag_clicked()
{
    Tag *tag = new Tag();
    tag->set_tag(ui->te_create_tag->toPlainText());
    DbTag::isCreate(tag);
    this->_table_model->select();
    delete tag;
}

void TagView::on_b_update_tag_clicked()
{
    if(this->_selected_tag != nullptr){
        this->_selected_tag->set_tag(ui->te_create_tag->toPlainText());
        if(DbTag::isUpdate(this->_selected_tag)){
            this->_table_model->select();
        }
    }
}

void TagView::on_b_remove_tag_clicked()
{
    if(this->_selected_tag != nullptr){
        if(DbTag::isRemoved(this->_selected_tag->get_id())){
            this->_table_model->select();
            this->_selected_tag = nullptr;
        }
    }
}

void TagView::on_lv_created_tags_clicked(const QModelIndex &index)
{
   int id, id_column_index, tag_column_index;
   QString tag;

   id_column_index = this->_table_model->record().indexOf(COLUMN_ID);
   tag_column_index = this->_table_model->record().indexOf(COLUMN_TAG);

   id = this->_table_model->index(index.row(), id_column_index).data(Qt::DisplayRole).toInt();
   tag = this->_table_model->index(index.row(), tag_column_index).data(Qt::DisplayRole).toString();

   this->_selected_tag = new Tag(id, tag);

   this->ui->te_create_tag->setText(tag);
}

