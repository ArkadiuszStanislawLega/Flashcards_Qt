#include "questionmodelsql.h"

QuestionModelSql::QuestionModelSql(Question *model, QObject *parent)
    : QObject{parent} {
  this->_model = model;
}

bool QuestionModelSql::isInsertedSql() {
  if (!this->_model) {
    throw std::invalid_argument(
        "QuestionModelSql::isInsertedSql -- pointer to question is null.");
  }
  InsertSql insert = InsertSql(
      TABLE_QUESTIONS, {COLUMN_VALUE, COLUMN_ANSWER, COLUMN_IS_ACTIVE},
      {this->_model->getValue(), this->_model->getAnswer(),
       this->_model->getIsActive() ? "1" : "0"},
      this);

  if (!insert.generate().exec()) {
    throw std::invalid_argument(
        "QuestionModelSql::isInsertSql -- query failed to execute.");
  }
  this->findByCriteria();
  return true;
}

Question *QuestionModelSql::selectQuestion(int id) {
  if (id <= 0) {
    throw std::invalid_argument(
        "QuestionModelSql::selectQuestion - property id is zero or subzero.");
  }

  FindByKeySql *sql = new FindByKeySql(TABLE_QUESTIONS, id, {}, this);
  QSqlQuery query = sql->generate();

  if (!query.exec()) {
    throw std::invalid_argument(
        "QuestionSql::selectQuestion - the query failed.");
  }

  this->_model->setId(QueryToValueConverter::get<int>(&query, COLUMN_ID));
  this->_model->setAnswer(
      QueryToValueConverter::get<QString>(&query, COLUMN_ANSWER));
  this->_model->setValue(
      QueryToValueConverter::get<QString>(&query, COLUMN_VALUE));
  this->_model->setIsActive(
      QueryToValueConverter::get<bool>(&query, COLUMN_IS_ACTIVE));

  return this->_model;
}

Question *QuestionModelSql::findByCriteria() {
  if (this->_model->getValue().isEmpty()) {
    throw std::invalid_argument(
        "QuestionModelSql::selectQuestion -- value is empty.");
  }
  if (this->_model->getAnswer().isEmpty()) {
    throw std::invalid_argument(
        "QuestionModelSql::selectQuestion -- answer is empty.");
  }
  QString criteria = COLUMN_VALUE + " = " + this->_model->getValue() + ", " +
                     COLUMN_ANSWER + " = " + this->_model->getAnswer();

  SelectWithCriteriaSql sql = SelectWithCriteriaSql(
      TABLE_QUESTIONS, {COLUMN_VALUE, COLUMN_ANSWER}, criteria, this);

  QSqlQuery query;
  query.prepare(sql.generate());

  if (!query.exec()) {
    throw std::invalid_argument(
        "QuestionSql::selectQuestion - the query failed.");
  }
  this->_model->setId(QueryToValueConverter::get<int>(&query, COLUMN_ID));
  this->_model->setAnswer(
      QueryToValueConverter::get<QString>(&query, COLUMN_ANSWER));
  this->_model->setValue(
      QueryToValueConverter::get<QString>(&query, COLUMN_VALUE));
  this->_model->setIsActive(
      QueryToValueConverter::get<bool>(&query, COLUMN_IS_ACTIVE));

  qDebug() << this->_model->getId();

  return this->_model;
}
