#ifndef TAGMODELSQL_H
#define TAGMODELSQL_H

#include <Models/tag.h>
#include <QObject>
#include <Converters/fromquerytovalueconverter.h>
#include <Database/SqlGenerators/deletesql.h>
#include <Database/SqlGenerators/findbykeysql.h>
#include <Database/SqlGenerators/insertsql.h>
#include <Database/SqlGenerators/selectsql.h>
#include <Database/SqlGenerators/selectwithcriteriasql.h>
#include <Database/SqlGenerators/updatesql.h>
#include <Converters/fromquerytotagconverter.h>

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
  QList<Tag *> getAllTags();
signals:
};

#endif // TAGMODELSQL_H
