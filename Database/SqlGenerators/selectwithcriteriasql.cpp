#include "selectwithcriteriasql.h"

SelectWithCriteriaSql::SelectWithCriteriaSql(QString table,
                                             QList<QString> columns,
                                             QString criteria, QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
  this->_criteria = criteria;
}

QString SelectWithCriteriaSql::generate() {
  assert(!this->_table.isEmpty());

  QString query;
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

  query += " " + FROM + this->_table;
  query += " " + WHERE + this->_criteria;
  return query;
}
