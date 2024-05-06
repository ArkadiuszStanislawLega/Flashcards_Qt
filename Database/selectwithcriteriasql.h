#ifndef SELECTWITHCRITERIASQL_H
#define SELECTWITHCRITERIASQL_H

#include <QObject>

class selectWithCriteriaSql : public QObject {
private:
  Q_OBJECT
  QString _table, _criteria;
  QList<QString> _columns;

public:
  explicit selectWithCriteriaSql(QString table, QList<QString> columns,
                                  QString conditions,
                                  QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // SELECTWITHCRITERIASQL_H
