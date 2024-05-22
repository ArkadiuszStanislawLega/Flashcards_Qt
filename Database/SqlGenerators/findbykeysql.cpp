#include "findbykeysql.h"

#include <stringmanager.h>

FindByKeySql::FindByKeySql(QString table, QList<QString> columns,
                           QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
}

QString FindByKeySql::generate() {
  if (this->_table.isEmpty()) {
    throw std::invalid_argument("Property table (name) - is empty.");
  }

  QString query{};
  query = SELECT;

  if (this->_columns.empty()) {
    query += " * ";
  } else {
    for (int i{}; i < this->_columns.size(); i++) {
      query += this->_columns.at(i);
      if (i < this->_columns.size() - 1) {
        query += ", ";
      }
    }
  }
  query = FROM + this->_table + " " + WHERE +
          StringManager::get(StringID::ColumnId) +
          " = (:" + StringManager::get(StringID::ColumnId) + ") LIMIT 1";

  return query;
}
