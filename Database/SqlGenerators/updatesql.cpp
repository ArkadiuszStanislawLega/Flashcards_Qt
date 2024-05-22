#include "updatesql.h"
#include "Constants/strings.h"

#include <stringmanager.h>

UpdateSql::UpdateSql(QString table, QList<QString> columns, QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
}

QString UpdateSql::generate() {
  QString query{};

  query = UPDATE + this->_table + " " + SET;
  for (int i{}; i < this->_columns.size(); i++) {
    query += this->_columns[i] + "=:" + this->_columns[i];
    if (i < this->_columns.size() - 1) {
      query += ", ";
    }
  }
  query += " " + WHERE + StringManager::get(StringID::ColumnId) +
           " = :" + StringManager::get(StringID::ColumnId);
  return query;
}
