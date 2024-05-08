#include "questionmodelsql.h"

#include "findbykeysql.h"

QuestionModelSql::QuestionModelSql(Question *model, QObject *parent)
    : QObject{parent} {
  this->_model = model;
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
