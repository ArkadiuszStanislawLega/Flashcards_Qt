#include "selectwithjoinsql.h"
#include "Constants/strings.h"

SelectWithJoinSql::SelectWithJoinSql(
    QString table, QList<QString> requiredColumns,
    QList<std::pair<QString, QString>> connectedTables,
    QList<std::pair<QString, QString>> connectedValues, QString criteria,
    QObject *parent)
    : QObject(parent) {
  this->_table = table;
  this->_requiredColumns = requiredColumns;
  this->_connectedTables = connectedTables;
  this->_connectedValues = connectedValues;
  this->_criteria = criteria;
}

QString SelectWithJoinSql::generate() {
  assert(!this->_table.isEmpty());
  assert(!this->_connectedTables.isEmpty());
  assert(!this->_connectedValues.isEmpty());
  assert(!this->_criteria.isEmpty());
  assert(this->_connectedValues.size() == this->_connectedTables.size());

  QString query;
  query = SELECT;

  if (this->_requiredColumns.empty()) {
    query += " * ";
  } else {
    for (int i{}; i < this->_requiredColumns.size(); i++) {
      query += this->_requiredColumns.at(i);

      if (i < this->_requiredColumns.size() - 1) {
        query += ", ";
      }
    }
  }

  query += " " + FROM + this->_table + " ";

  for (int i{}; i < this->_connectedTables.size(); i++) {
    query += INNER_JOIN + this->_connectedTables[i].first + " " + ON +
             this->_connectedTables[i].first + "." +
             this->_connectedValues[i].first + "=" +
             this->_connectedTables[i].second + "." +
             this->_connectedValues[i].second + " ";
  }

  query += WHERE + this->_criteria;

  return query;
}
