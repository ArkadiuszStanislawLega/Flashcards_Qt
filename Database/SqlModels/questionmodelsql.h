#ifndef QUESTIONMODELSQL_H
#define QUESTIONMODELSQL_H

#include <QObject>

#include <Converters/fromquerytoquestionconverter.h>
#include <Database/SqlGenerators/deletesql.h>
#include <Database/SqlGenerators/findbykeysql.h>
#include <Database/SqlGenerators/insertsql.h>
#include <Database/SqlGenerators/selectsql.h>
#include <Database/SqlGenerators/selectwithcriteriasql.h>
#include <Database/SqlGenerators/updatesql.h>
#include <Database/SqlGenerators/wheresql.h>
#include <Models/question.h>

class QuestionModelSql : public QObject {
private:
  Q_OBJECT
  Question *_model;

  template <class T>
  T getQualityFromQuery(QSqlQuery *query, QString coulmnName);
  void convertQueryToQuestion(QSqlQuery *query);

public:
  explicit QuestionModelSql(Question *model, QObject *parent = nullptr);
  bool isInsertedSql();
  bool isDeleteSql();
  bool updateSql();
  Question *selectQuestion(int id);
  Question *findByCriteria();

signals:
};

#endif // QUESTIONMODELSQL_H
