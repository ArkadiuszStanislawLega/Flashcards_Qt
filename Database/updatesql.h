#ifndef UPDATESQL_H
#define UPDATESQL_H

#include <QObject>
#include <QSqlQuery>

class UpdateSql : public QObject {
private:
  Q_OBJECT

public:
  explicit UpdateSql(QObject *parent = nullptr);
  QSqlQuery generate();

signals:
};

#endif // UPDATESQL_H
