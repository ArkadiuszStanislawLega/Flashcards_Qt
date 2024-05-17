#ifndef SELECTWITHJOINSQL_H
#define SELECTWITHJOINSQL_H

#include <QObject>

class SelectWithJoinSql : public QObject {
private:
  Q_OBJECT
  QString _table, _criteria;
  QList<QString> _columns;
  QList<std::pair<QString, QString>> _tables, _values;

public:
  explicit SelectWithJoinSql(QString table, QList<QString> columns,
                             QList<std::pair<QString, QString>> tables,
                             QList<std::pair<QString, QString>> values,
                             QString criteria, QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // SELECTWITHJOINSQL_H
