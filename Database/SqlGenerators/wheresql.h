#ifndef WHERESQL_H
#define WHERESQL_H

#include <QObject>

class WhereSql : public QObject {
private:
  Q_OBJECT
  QString _criteria;

public:
  explicit WhereSql(QString riteria, QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // WHERESQL_H
