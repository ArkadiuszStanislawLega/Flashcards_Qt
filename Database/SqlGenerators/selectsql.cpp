#include "selectsql.h"
#include "Constants/strings.h"

///
/// \brief SelectSql::SelectSql
/// \param table Table is required argument
/// \param columns Can be emty list then if query will be generated all columns
/// will be recived. \param parent Parent of the object.
///
SelectSql::SelectSql(QString table, QList<QString> columns, QObject *parent)
    : QObject{parent} {
  this->_table = table;
  this->_columns = columns;
}

///
/// \brief SelectSql::generate Generate SELECT sql query, if property coulumns
/// empty get all columns from database. \return SelectSql Query to database.
///
QString SelectSql::generate() {
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

  query += FROM + this->_table;
  return query;
}
