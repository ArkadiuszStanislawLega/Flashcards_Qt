#ifndef TAGMODELSQL_H
#define TAGMODELSQL_H

#include "../Models/tag.h"
#include <QObject>

class TagModelSql : public QObject {
private:
  Q_OBJECT
  Tag *_model;
  void convertQueryToTag(QSqlQuery *query);

public:
  explicit TagModelSql(Tag *model, QObject *parent = nullptr);
  bool isInsertedSql();
  bool isDeleteSql();
  bool updateSql();
  Tag *selectTag(int id);
  Tag *findByCriteria();

signals:
};

#endif // TAGMODELSQL_H
