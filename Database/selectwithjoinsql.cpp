#include "selectwithjoinsql.h"
#include "Constants/strings.h"

SelectWithJoinSql::SelectWithJoinSql(QString table, QList<QString> columns,
                                     QList<std::pair<QString, QString>> tables,
                                     QList<std::pair<QString, QString>> values,
                                     QString criteria, QObject *parent)
    : QObject(parent) {
  this->_table = table;
  this->_columns = columns;
  this->_tables = tables;
  this->_values = values;
  this->_criteria = criteria;
}

QString SelectWithJoinSql::generate() {
  if (this->_table.isEmpty()) {
    throw std::invalid_argument(
        "SelectWithJoinSql::generate -- property table is empty.");
  }

  if (this->_criteria.isEmpty()) {
    throw std::invalid_argument(
        "SelectWithJoinSql::generate -- property criteria is empty.");
  }

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

  query += " " + FROM + this->_table + " ";

  for (int i{}; i < this->_tables.size(); i++) {
    query += INNER_JOIN + this->_tables[i].first + " " + ON +
             this->_tables[i].first + "." + this->_values[i].first + "=" +
             this->_tables[i].second + "." + this->_values[i].second + " ";
  }

  query += WHERE + this->_criteria;

  return query;
}
