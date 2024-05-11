#ifndef QUESTIONMODELSQL_H
#define QUESTIONMODELSQL_H

#include <QObject>

#include "../Converters/querytovalueconverter.h"
#include "../Models/question.h"
#include "findbykeysql.h"
#include "insertsql.h"
#include "selectsql.h"
#include "selectwithcriteriasql.h"
#include "wheresql.h"

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
  Question *selectQuestion(int id);
  Question *findByCriteria();

signals:
};

#endif // QUESTIONMODELSQL_H
