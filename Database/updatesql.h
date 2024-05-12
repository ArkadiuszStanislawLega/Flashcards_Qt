#ifndef UPDATESQL_H
#define UPDATESQL_H

#include <QObject>
#include <QSqlQuery>

class UpdateSql : public QObject {
private:
  Q_OBJECT
  QString _table;
  QList<QString> _columns;

public:
  explicit UpdateSql(QString table, QList<QString> columns,
                     QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // UPDATESQL_H
