#include "insertsql.h"
#include "Constants/strings.h"

InsertSql::InsertSql(QString table, QList<QString> columns, QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
}

QString InsertSql::generate() {
  if (this->_table.isEmpty()) {
    throw std::invalid_argument("Property table is empty.");
  }

  if (this->_columns.empty()) {
    throw std::invalid_argument("Property columns is empty.");
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
