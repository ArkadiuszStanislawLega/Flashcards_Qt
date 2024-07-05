#include "insertsql.h"
#include "Constants/strings.h"

InsertSql::InsertSql(QString table, QList<QString> columns, QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
}

QString InsertSql::generate() {
  assert(!this->_table.isEmpty());
  assert(!this->_columns.empty());

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
