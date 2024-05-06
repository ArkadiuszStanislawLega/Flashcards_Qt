#ifndef SELECT_H
#define SELECT_H

#include <QObject>

class Select : public QObject {
  Q_OBJECT
  QString _table;
  QList<QString> _columns;

public:
  explicit Select(QString table, QList<QString> colmuns,
                  QObject *parent = nullptr);

  // Sql interface
public:
  QString genarte();
};

#endif // SELECT_H
