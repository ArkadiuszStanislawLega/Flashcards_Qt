#include "tagview.h"

#include <stringmanager.h>

#include <Exceptions/nullpointertoquestionandtagexception.h>
#include <Exceptions/queryfiledexception.h>

TagView::TagView(QWidget *parent) : QWidget{parent}, ui(new Ui::TagView) {
  ui->setupUi(this);
  this->_selected_tag = nullptr;
  this->initialTagsListView();
}

void TagView::printInfo(const QString &value, bool isError) {
  QPalette pal = this->ui->l_info->palette();
  pal.setColor(QPalette::Window, QColor(isError ? Qt::red : Qt::transparent));

  this->ui->l_info->setText(value);
  this->ui->l_info->setPalette(pal);
}

void TagView::cleanTextEditors() { this->ui->te_create_tag->clear(); }

void TagView::initialTagsListView() {
  this->_table_model = new QSqlRelationalTableModel;
  this->_table_model->setTable(StringManager::get(StringID::TableTags));
  this->_table_model->select();

  this->ui->lv_created_tags->setModel(this->_table_model);
  this->ui->lv_created_tags->setModelColumn(
      this->_table_model->record().indexOf(
          StringManager::get(StringID::ColumnTag)));
}

void TagView::on_b_create_tag_clicked() {
  if (ui->te_create_tag->toPlainText().isEmpty()) {
    this->printInfo(StringManager::get(StringID::FieldTagCantEmpty), true);
    return;
  }

  TagModelSql query = TagModelSql(
      new Tag(ui->te_create_tag->toPlainText().toStdString().c_str()), this);

  try {
    if (query.isInsertedSql()) {
      this->printInfo(StringManager::get(StringID::TagCreatedCorrectly));
    }

    this->_table_model->select();
    this->cleanTextEditors();
    emit added_tag_to_db();

  } catch (std::invalid_argument &e) {
    qWarning() << "TagView::no_b_create_tag_clicked" << e.what();
    this->printInfo(StringManager::get(StringID::ErrorDatabase), true);
  }
}

void TagView::on_b_update_tag_clicked() {
  if (this->ui->te_create_tag->toPlainText().isEmpty()) {
    this->printInfo(StringManager::get(StringID::FieldTagCantEmpty), true);
    return;
  }

  if (!this->_selected_tag) {
    this->printInfo(StringManager::get(StringID::SelectTagFirst), true);
    return;
  }

  this->_selected_tag->setTag(ui->te_create_tag->toPlainText());
  TagModelSql query = TagModelSql(this->_selected_tag, this);

  try {
    if (query.updateSql()) {
      this->_table_model->select();
      this->printInfo(StringManager::get(StringID::TagUpdateSuccesfully));
    }

    this->cleanTextEditors();
    emit updated_tag_from_db();

  } catch (std::invalid_argument &e) {
    qWarning() << "TagView::on_b_update_tag_clicked" << e.what();
    this->printInfo(StringManager::get(StringID::ErrorDatabase), true);
  }
}

void TagView::on_b_remove_tag_clicked() {
  const char *methodName = "on_b_remove_tag_clicked";
  if (!this->_selected_tag) {
    this->printInfo(StringManager::get(StringID::SelectTagFirst), true);
    return;
  }

  TagModelSql query = TagModelSql(this->_selected_tag, this);
  TagAndQuestionRelationSql relation =
      TagAndQuestionRelationSql(this->_selected_tag, new Question(this), this);

  try {
    if (relation.isAllRelationRemoved() && query.isDeleteSql()) {
      this->_table_model->select();
      this->_selected_tag = nullptr;
      this->printInfo(StringManager::get(StringID::TagSuccesfullyRemoved));
    }

    this->cleanTextEditors();
    emit remove_tag_from_db();

  } catch (NullPointerToQuestionAndTagException &e) {
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
    this->printInfo(StringManager::get(StringID::UnexpectedError), true);
  } catch (QueryFiledException &e) {
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
    this->printInfo(StringManager::get(StringID::ErrorDatabase), true);
  }
}

void TagView::on_lv_created_tags_clicked(const QModelIndex &index) {
  int id, id_column_index, tag_column_index;
  QString tag;

  id_column_index = this->_table_model->record().indexOf(
      StringManager::get(StringID::ColumnId));
  tag_column_index = this->_table_model->record().indexOf(
      StringManager::get(StringID::ColumnTag));

  id = this->_table_model->index(index.row(), id_column_index)
           .data(Qt::DisplayRole)
           .toInt();
  tag = this->_table_model->index(index.row(), tag_column_index)
            .data(Qt::DisplayRole)
            .toString();

  this->_selected_tag = new Tag(id, tag, this);

  this->ui->te_create_tag->setText(tag);
}
