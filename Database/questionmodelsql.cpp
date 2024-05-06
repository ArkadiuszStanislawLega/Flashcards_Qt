
#include "questionmodelsql.h"

QuestionModelSql::QuestionModelSql(Question *model, QObject *parent)
    : QObject{parent} {
  this->_model = model;
}

template <typename T>
T QuestionModelSql::getQualityFromQuery(QSqlQuery *query, QString columnName) {
  if (!query) {
    throw std::invalid_argument("Query is empty.");
  }

  if (columnName.isEmpty()) {
    throw std::invalid_argument("Colmun name is empty.");
  }

  int columnIndex = query->record().indexOf(columnName);

  if (std::is_same_v<T, int>) {
    return query->value(columnIndex).toInt();
  }

  if (std::is_same_v<T, bool>) {
    return query->value(columnIndex).toBool();
  };

  return -1;
}

QString QuestionModelSql::getQStringFromQuery(QSqlQuery *query,
                                              QString columnName) {

  if (!query) {
    throw std::invalid_argument("Query is empty.");
  }

  if (columnName.isEmpty()) {
    throw std::invalid_argument("Column name is emtpy.");
  }

  int columnIndex = query->record().indexOf(columnName);
  return query->value(columnIndex).toString();
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

  this->_model->setId(getQualityFromQuery<int>(&query, COLUMN_ID));
  this->_model->setAnswer(getQStringFromQuery(&query, COLUMN_ANSWER));
  this->_model->setValue(getQStringFromQuery(&query, COLUMN_VALUE));
  this->_model->setIsActive(
      getQualityFromQuery<bool>(&query, COLUMN_IS_ACTIVE));

  return this->_model;
}
