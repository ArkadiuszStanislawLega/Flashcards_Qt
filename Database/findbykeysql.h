#ifndef FINDBYKEYSQL_H
#define FINDBYKEYSQL_H

#include "Constants/strings.h"
#include <QObject>
#include <QSqlQuery>

class FindByKeySql : public QObject {
private:
  Q_OBJECT
  QString _table;
  int _id;
  QList<QString> _columns;

public:
  explicit FindByKeySql(QString table, int id, QList<QString> coulmns,
                        QObject *parent = nullptr);
  QSqlQuery generate();

signals:
};

#endif // FINDBYKEYSQL_H
