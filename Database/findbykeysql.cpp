#include "findbykeysql.h"

FindByKeySql::FindByKeySql(QString table, int id, QList<QString> columns,
                           QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_id = id;
  this->_columns = columns;
}

QSqlQuery FindByKeySql::generate() {
  if (this->_table.isEmpty()) {
    throw std::invalid_argument("Property table (name) - is empty.");
  }

  if (this->_id <= 0) {
    throw std::invalid_argument("Property id is zero or subzero.");
  }

  QString sQuery{};
  sQuery = SELECT;

  if (this->_columns.empty()) {
    sQuery += " * ";
  } else {
    for (int i{}; i < this->_columns.size(); i++) {
      sQuery += this->_columns.at(i);
      if (i < this->_columns.size() - 1) {
        sQuery += ", ";
      }
    }
  }
  sQuery = FROM + this->_table + " " + WHERE + COLUMN_ID + " = (:" + COLUMN_ID +
           ") LIMIT 1";

  QSqlQuery query;
  query.prepare(sQuery);
  query.bindValue(":" + COLUMN_ID, this->_id);

  return query;
}
