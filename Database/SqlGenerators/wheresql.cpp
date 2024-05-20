#include "wheresql.h"
#include "Constants/strings.h"

WhereSql::WhereSql(QString criteria, QObject *parent) : QObject(parent) {
  this->_criteria = criteria;
}

QString WhereSql::generate() {
  QString query;
  query = " " + WHERE + this->_criteria;
  return query;
}
