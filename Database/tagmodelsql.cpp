#include "tagmodelsql.h"

#include "../Converters/querytovalueconverter.h"
#include "insertsql.h"
#include "selectwithcriteriasql.h"

void tagmodelsql::convertQueryToTag(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument(
        "TagModelSql::converterQueryToTag -- pointer to query is empty.");
  }
  this->_model->setId(QueryToValueConverter::get<int>(query, COLUMN_ID));
  this->_model->setTag(QueryToValueConverter::get<QString>(query, COLUMN_TAG));
}

tagmodelsql::tagmodelsql(Tag *model, QObject *parent) : QObject{parent} {
  this->_model = model;
}

bool tagmodelsql::isInsertedSql() {
  if (!this->_model) {
    throw std::invalid_argument(
        "TagModelSql::isInsertedSql -- pointer to property model is empty.");
  }

  InsertSql sql = InsertSql(TABLE_TAGS, {COLUMN_TAG}, this);
  QSqlQuery query;
  query.prepare(sql.generate());
  query.bindValue(":" + COLUMN_TAG, this->_model->getTag());

  if (!query.exec()) {
    throw std::invalid_argument("TagModelSql::isInsertedSql -- query failed.");
  }
  return true;
}

bool tagmodelsql::isDeleteSql() { return true; }

bool tagmodelsql::updateSql() { return true; }

Tag *tagmodelsql::selectQuestion(int id) {
  Tag *t;
  return t;
}

Tag *tagmodelsql::findByCriteria() {
  if (this->_model->getTag().isEmpty()) {
    throw std::invalid_argument(
        "TagModelSql::findByCriteria -- value is empty.");
  }
  QString criteria = COLUMN_TAG + "=:" + COLUMN_TAG;

  SelectWithCriteriaSql select =
      SelectWithCriteriaSql(TABLE_TAGS, {}, criteria, this);

  QSqlQuery query;
  query.prepare(select.generate());
  query.bindValue(":" + COLUMN_TAG, this->_model->getTag());

  if (!query.exec()) {
    throw std::invalid_argument(
        "TagModelSql::findByCriteria - the query failed.");
  }

  if (!query.next()) {
    throw std::invalid_argument(
        "TagModelSql::findByCriteria - can't find question in database.");
  }

  try {
    this->convertQueryToTag(&query);
  } catch (std::invalid_argument &e) {
    qWarning() << "TagModelSql::findByCriteria -- " << e.what();
  }

  return this->_model;
}
