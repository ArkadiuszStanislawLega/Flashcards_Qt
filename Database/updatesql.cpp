#include "updatesql.h"

UpdateSql::UpdateSql(QObject *parent) : QObject{parent} {}

QSqlQuery UpdateSql::generate() { return QSqlQuery(); }
