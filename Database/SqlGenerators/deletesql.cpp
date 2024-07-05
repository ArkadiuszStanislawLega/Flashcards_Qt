#include "deletesql.h"
#include "Constants/strings.h"

DeleteSql::DeleteSql(QString table, QList<QString> columns, QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
}

QString DeleteSql::generate() {
  assert(!this->_table.isEmpty());
  assert(!this->_columns.empty());

  QString query{};

  query = DELETE + this->_table + " " + WHERE;
  for (int i{}; i < this->_columns.size(); i++) {
    query += this->_columns[i] + "=:" + this->_columns[i];
    if (i < this->_columns.size() - 1) {
      query += " " + AND;
    }
  }
  return query;
}
