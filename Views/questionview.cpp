#include "questionview.h"

#include <stringmanager.h>

#include <Exceptions/defaultexception.h>
#include <Exceptions/nullpointertoquestionandtagexception.h>
#include <Exceptions/nullpointertotagexception.h>

void QuestionView::initialQuestionsListView() {
  this->_table_model = new QSqlRelationalTableModel;
  this->_table_model->setTable(StringManager::get(StringID::TableQuestions));
  this->_table_model->setSort(this->_table_model->record().indexOf(
                                  StringManager::get(StringID::ColumnValue)),
                              Qt::AscendingOrder);
  this->_table_model->select();

  this->ui->lv_created_quesions->setModel(this->_table_model);
  this->ui->lv_created_quesions->setModelColumn(
      this->_table_model->record().indexOf(
          StringManager::get(StringID::ColumnValue)));
}

void QuestionView::initialTagsComboBoxData() {
  this->_cb_tags_model = new QSqlRelationalTableModel;
  this->_cb_tags_model->setTable(StringManager::get(StringID::TableTags));
  this->_cb_tags_model->select();
  this->ui->cb_tags->setModel(this->_cb_tags_model);
  this->ui->cb_tags->setModelColumn(this->_cb_tags_model->record().indexOf(
      StringManager::get(StringID::ColumnTag)));
}

void QuestionView::cleanTextEditors() {
  this->ui->te_value->clear();
  this->ui->te_answer->clear();
}

void QuestionView::printInfo(const QString &value, bool isError = false) {
  QPalette pal = this->ui->l_info->palette();
  pal.setColor(QPalette::Window, QColor(isError ? Qt::red : Qt::transparent));

  this->ui->l_info->setText(value);
  this->ui->l_info->setPalette(pal);
}

QuestionView::QuestionView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::QuestionView) {
  this->ui->setupUi(this);
  this->_selected_question = new Question(this);
  this->initialQuestionsListView();
  this->initialTagsComboBoxData();
}

void QuestionView::on_b_create_question_clicked() {
  if (ui->te_answer->toPlainText().isEmpty()) {
    this->printInfo(StringManager::get(StringID::FieldAnswerCantEmpty), true);
    return;
  }

  if (ui->te_value->toPlainText().isEmpty()) {
    this->printInfo(StringManager::get(StringID::FieldValueCantEmpty), true);
    return;
  }

  this->createRelationQuestionAndTag(addQuestionToDb());
  this->cleanTextEditors();

  emit added_question_to_db();
}

///
/// \brief QuestionView::addQuestionToDb Create question in database.
/// \return Created question with Id from database.
///
Question *QuestionView::addQuestionToDb() {
  const char *methodName = "addQuestionToDb";

  Question *q = new Question(this);
  q->setAnswer(ui->te_answer->toPlainText());
  q->setValue(ui->te_value->toPlainText());
  q->setIsActive(ui->rb_isActive->isChecked());

  QuestionModelSql sqlModel = QuestionModelSql(q, this);

  try {
    if (sqlModel.isInsertedSql()) {
      this->_table_model->select();
      this->cleanTextEditors();
      this->printInfo(StringManager::get(StringID::QuestionCreatedCorrectly));
    }
  } catch (NullPointerToQuestionException &e) {
    this->printInfo(StringManager::get(StringID::UnexpectedError), true);
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
  } catch (QueryFiledException &e) {
    this->printInfo(StringManager::get(StringID::ErrorDatabase), true);
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
  }

  return q;
}

void QuestionView::createRelationQuestionAndTag(Question *q) {
  const char *methodName = "createRelationQuestionAndTag";
  if (!q) {
    throw NullPointerToQuestionException(this->metaObject()->className(),
                                         methodName);
  }

  if (!this->_selected_tag) {
    throw NullPointerToTagException(this->metaObject()->className(),
                                    methodName);
  }

  if (q->getId() <= 0 || this->_selected_tag->getId() <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  if (q && this->_selected_tag) {
    TagAndQuestionRelationSql relation =
        TagAndQuestionRelationSql(this->_selected_tag, q, this);
    relation.isInsertedSql();

    delete q;
  }
}

void QuestionView::on_b_update_question_clicked() {
  const char *methodName = "on_b_update_question_clicked";

  if (!this->_selected_question) {
    this->printInfo(StringManager::get(StringID::InfoFirstSelectQuestion),
                    true);
    return;
  }

  if (ui->te_answer->toPlainText().isEmpty()) {
    this->printInfo(StringManager::get(StringID::FieldAnswerCantEmpty), true);
    return;
  }

  if (ui->te_value->toPlainText().isEmpty()) {
    this->printInfo(StringManager::get(StringID::FieldValueCantEmpty), true);
    return;
  }

  this->_selected_question->setAnswer(this->ui->te_answer->toPlainText());
  this->_selected_question->setValue(this->ui->te_value->toPlainText());
  this->_selected_question->setIsActive(this->ui->rb_isActive->isChecked());

  QuestionModelSql sqlModel = QuestionModelSql(this->_selected_question, this);

  try {
    if (sqlModel.updateSql()) {
      this->_table_model->select();
      this->printInfo(StringManager::get(StringID::QuestionUpdated));
      this->cleanTextEditors();
    }
    emit update_question_from_db();
  } catch (NullPointerToQuestionException &e) {
    this->printInfo(StringManager::get(StringID::UnexpectedError), true);
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
  } catch (BelowZeroIdException &e) {
    this->printInfo(StringManager::get(StringID::UnexpectedError), true);
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
  } catch (QueryFiledException &e) {
    this->printInfo(StringManager::get(StringID::ErrorDatabase), true);
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
  }
}

void QuestionView::on_b_remove_question_clicked() {
  const char *methodName = "on_b_remove_question_clicked";

  if (this->_selected_question == nullptr) {
    this->printInfo(StringManager::get(StringID::InfoFirstSelectQuestion),
                    true);
    return;
  }

  if (this->_selected_question->getId() <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  QuestionModelSql sqlModel = QuestionModelSql(this->_selected_question, this);
  TagAndQuestionRelationSql relation =
      TagAndQuestionRelationSql(new Tag(this), this->_selected_question, this);

  try {
    if (relation.isAllRelationRemoved() && sqlModel.isDeleteSql()) {
      this->_selected_question = nullptr;
      this->_table_model->select();
      this->cleanTextEditors();
      this->printInfo(StringManager::get(StringID::QuestionSuccesfullyRemoved));
    }
    emit remove_question_from_db();
  } catch (QueryFiledException &e) {
    this->printInfo(StringManager::get(StringID::ErrorDatabase), true);
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
  } catch (NullPointerToQuestionAndTagException &e) {
    this->printInfo(StringManager::get(StringID::UnexpectedError), true);
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
  }
}

void QuestionView::on_lv_created_quesions_pressed(const QModelIndex &index) {
  const char *methodName = "on_lv_created_quesions_pressed";
  int id, id_column_index, value_column_index, answer_column_index,
      is_active_column_index;

  QString value, answer;
  bool isActive;

  id_column_index = this->_table_model->record().indexOf(
      StringManager::get(StringID::ColumnId));
  value_column_index = this->_table_model->record().indexOf(
      StringManager::get(StringID::ColumnValue));
  answer_column_index = this->_table_model->record().indexOf(
      StringManager::get(StringID::ColumnAnswer));

  is_active_column_index = this->_table_model->record().indexOf(
      StringManager::get(StringID::ColumnIsActive));

  id = this->_table_model->index(index.row(), id_column_index)
           .data(Qt::DisplayRole)
           .toInt();
  value = this->_table_model->index(index.row(), value_column_index)
              .data(Qt::DisplayRole)
              .toString();
  answer = this->_table_model->index(index.row(), answer_column_index)
               .data(Qt::DisplayRole)
               .toString();

  isActive = this->_table_model->index(index.row(), is_active_column_index)
                 .data(Qt::DisplayRole)
                 .toBool();

  try {

    this->_selected_question = new Question(id, value, answer, isActive, {});
    TagAndQuestionRelationSql *relation =
        new TagAndQuestionRelationSql(nullptr, this->_selected_question, this);

    this->_selected_question->setTags(relation->getRelatedTags());
    this->_selected_question->setParent(this);
  } catch (NullPointerToQuestionException &e) {
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
    this->printInfo(StringManager::get(StringID::UnexpectedError), true);
  } catch (BelowZeroIdException &e) {
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
    this->printInfo(StringManager::get(StringID::UnexpectedError), true);
  } catch (QueryFiledException &e) {
    qWarning() << this->metaObject()->className() << "::" << methodName
               << e.what();
    this->printInfo(StringManager::get(StringID::ErrorDatabase), true);
  }

  this->ui->te_answer->setText(answer);
  this->ui->te_value->setText(value);
  this->ui->rb_isActive->setChecked(isActive);
}

void QuestionView::on_cb_tags_currentIndexChanged(int index) {
  int id, id_column, tag_column_index;
  QString tag;

  id_column = this->_cb_tags_model->record().indexOf(
      StringManager::get(StringID::ColumnId));
  tag_column_index = this->_cb_tags_model->record().indexOf(
      StringManager::get(StringID::ColumnTag));

  id = this->_cb_tags_model->index(index, id_column)
           .data(Qt::DisplayRole)
           .toInt();
  tag = this->_cb_tags_model->index(index, tag_column_index)
            .data(Qt::DisplayRole)
            .toString();

  this->_selected_tag = new Tag(id, tag, this);
}

void QuestionView::on_le_searching_bar_textChanged(const QString &arg1) {
  this->_table_model->setFilter(
      StringManager::get(StringID::TableQuestions) + "." +
      StringManager::get(StringID::ColumnValue) + " LIKE \"%" + arg1 + "%\"");
  this->_table_model->select();
}

void QuestionView::added_tag_to_db() { this->_cb_tags_model->select(); }
