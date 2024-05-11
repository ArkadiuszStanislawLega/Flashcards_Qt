#include "deletesql.h"
#include "Constants/strings.h"

DeleteSql::DeleteSql(QString table, QList<QString> columns, QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
}

QString DeleteSql::generate() {
  if (this->_table.isEmpty()) {
    throw std::invalid_argument("DeleteSql::generate -- table name is empty.");
  }

  if (this->_columns.empty()) {
    throw std::invalid_argument(
        "DeleteSql::generate -- list with coulmns is emtpy.");
  }

  QString query{};

  query = DELETE + this->_table + " " + WHERE;
  for (int i{}; i < this->_columns.size(); i++) {
    query += this->_columns[i] + "=:" + this->_columns[i];
    if (i < this->_columns.size() - 1) {
      query += AND;
    }
  }
  return query;
}
