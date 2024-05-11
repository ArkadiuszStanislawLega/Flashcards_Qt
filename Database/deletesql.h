#ifndef DELETESQL_H
#define DELETESQL_H

#include <QObject>

class DeleteSql : public QObject {
private:
  Q_OBJECT
  QString _table;
  QList<QString> _columns;

public:
  explicit DeleteSql(QString table, QList<QString> columns,
                     QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // DELETESQL_H
