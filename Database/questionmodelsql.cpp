#include "questionmodelsql.h"

template <typename T>
T QuestionModelSql::getQualityFromQuery(QSqlQuery *query, QString columnName) {
  if (!query) {
    throw std::invalid_argument("Query is empty.");
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
  int columnIndex = query->record().indexOf(columnName);
  return query->value(columnIndex).toString();
}

QuestionModelSql::QuestionModelSql(Question *model, QObject *parent)
    : QObject{parent} {
  this->_model = model;
}

Question *QuestionModelSql::selectQuesiton(int id) {
  if (id <= 0) {
    throw std::invalid_argument("QuestionModelSql::selectQuestion - id = 0");
  }

  QSqlQuery query;

  SelectSql *selectSql = new SelectSql(TABLE_QUESTIONS, {}, this);
  WhereSql *whereSql =
      new WhereSql(COLUMN_ID + " = (:" + COLUMN_ID + ") LIMIT 1");

  QString select = selectSql->generate();
  QString where = whereSql->generate();

  query.prepare(select + where);
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
