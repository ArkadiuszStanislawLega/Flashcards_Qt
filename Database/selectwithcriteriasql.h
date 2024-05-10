#ifndef SELECTWITHCRITERIASQL_H
#define SELECTWITHCRITERIASQL_H

#include "Constants/strings.h"
#include <QObject>
#include <QSqlQuery>

class SelectWithCriteriaSql : public QObject {
private:
  Q_OBJECT
  QString _table, _criteria;
  QList<QString> _columns;

public:
  explicit SelectWithCriteriaSql(QString table, QList<QString> columns,
                                 QString conditions, QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // SELECTWITHCRITERIASQL_H
