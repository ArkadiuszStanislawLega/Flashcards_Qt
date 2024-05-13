#ifndef TAGMODELSQL_H
#define TAGMODELSQL_H

#include "../Models/tag.h"
#include <QObject>

class tagmodelsql : public QObject {
private:
  Q_OBJECT
  Tag *_model;
  void convertQueryToTag(QSqlQuery *query);

public:
  explicit tagmodelsql(Tag *model, QObject *parent = nullptr);
  bool isInsertedSql();
  bool isDeleteSql();
  bool updateSql();
  Tag *selectQuestion(int id);
  Tag *findByCriteria();

signals:
};

#endif // TAGMODELSQL_H
