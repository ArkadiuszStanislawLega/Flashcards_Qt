#ifndef INSERTSQL_H
#define INSERTSQL_H

#include <QObject>
#include <QSqlQuery>

class InsertSql : public QObject {
private:
  Q_OBJECT
  QString _table;
  QList<QString> _columns;

public:
  explicit InsertSql(QString table, QList<QString> colmuns,
                     QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // INSERTSQL_H
