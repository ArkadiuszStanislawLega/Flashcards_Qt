
#include "questionmodelsql.h"

#include "../Converters/querytovalueconverter.h"

QuestionModelSql::QuestionModelSql(Question *model, QObject *parent)
    : QObject{parent} {
  this->_model = model;
}

Question *QuestionModelSql::selectQuestion(int id) {
  if (id <= 0) {
    throw std::invalid_argument(
        "QuestionModelSql::selectQuestion - property id is zero or subzero.");
  }

  QString criteria = COLUMN_ID + " = (:" + COLUMN_ID + ") LIMIT 1";
  SelectWithCriteriaSql *selectSql =
      new SelectWithCriteriaSql(TABLE_QUESTIONS, {}, criteria, this);

  QSqlQuery query;
  query.prepare(selectSql->generate());
  query.bindValue(":" + COLUMN_ID, id);

  if (!query.exec()) {
    throw std::invalid_argument(
        "QuestionSql::selectQuestion - the query failed.");
  }

  this->_model->setId(QueryToValueConverter::get<int>(&query, COLUMN_ID));
  this->_model->setAnswer(QueryToValueConverter::get<QString>(&query, COLUMN_ANSWER));
  this->_model->setValue(QueryToValueConverter::get<QString>(&query, COLUMN_VALUE));
  this->_model->setIsActive(QueryToValueConverter::get<bool>(&query, COLUMN_IS_ACTIVE));

  return this->_model;
}
