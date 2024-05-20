#ifndef SELECTSQL_H
#define SELECTSQL_H

#include <QObject>

class SelectSql : public QObject {
  Q_OBJECT
  QString _table;
  QList<QString> _columns;

public:
  explicit SelectSql(QString table, QList<QString> colmuns,
                  QObject *parent = nullptr);

  // Sql interface
public:
  QString generate();
};

#endif // SELECTSQL_H
