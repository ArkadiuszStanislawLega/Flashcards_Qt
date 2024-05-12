#ifndef FINDBYKEYSQL_H
#define FINDBYKEYSQL_H

#include "Constants/strings.h"
#include <QObject>
#include <QSqlQuery>

class FindByKeySql : public QObject {
private:
  Q_OBJECT
  QString _table;
  QList<QString> _columns;

public:
  explicit FindByKeySql(QString table, QList<QString> coulmns,
                        QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // FINDBYKEYSQL_H
