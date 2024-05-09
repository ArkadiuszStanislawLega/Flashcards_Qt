#ifndef INSERTSQL_H
#define INSERTSQL_H

#include <QObject>
#include <QSqlQuery>

class InsertSql : public QObject {
private:
  Q_OBJECT
  QString _table;
  QList<QString> _values, _columns;

  QString prepareQuery();

public:
  explicit InsertSql(QString table, QList<QString> colmuns,
                     QList<QString> values, QObject *parent = nullptr);
  QSqlQuery generate();

signals:
};

#endif // INSERTSQL_H
