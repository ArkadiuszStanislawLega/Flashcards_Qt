#include "insertsql.h"
#include "Constants/strings.h"

InsertSql::InsertSql(QString table, QList<QString> columns,
                     QList<QString> values, QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
  this->_values = values;
}

QString InsertSql::prepareQuery() {
  if (this->_table.isEmpty()) {
    throw std::invalid_argument("Property table is empty.");
  }

  if (this->_columns.empty()) {
    throw std::invalid_argument("Property columns is empty.");
  }

  if (this->_values.empty()) {
    throw std::invalid_argument("Property value is empty.");
  }

  if (this->_values.size() != this->_columns.size()) {
    throw std::invalid_argument(
        "The columns and values properties must have the same size.");
  }

  QString sQuery{};

  sQuery = INSERT + this->_table + "(";

  for (int i{}; i < this->_columns.size(); i++) {
    sQuery += this->_columns[i];
    if (i < this->_columns.size() - 1) {
      sQuery += ", ";
    }
  }

  sQuery += ") " + VALUES + "(";

  for (int i{}; i < this->_columns.size(); i++) {
    sQuery += ":" + this->_columns[i];
    if (i < this->_columns.size() - 1) {
      sQuery += ", ";
    }
  }

  sQuery += ")";

  return sQuery;
}

QSqlQuery InsertSql::generate() {
  QString qString = prepareQuery();

  if (qString.isEmpty()) {
    throw std::invalid_argument("Query can not be empty.");
  }

  QSqlQuery query;
  query.prepare(prepareQuery());

  for (int i{}; i < this->_values.size(); i++) {
    query.bindValue(":" + this->_columns[i], this->_values[i]);
  }

  return query;
}
