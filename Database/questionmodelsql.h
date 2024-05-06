#ifndef QUESTIONMODELSQL_H
#define QUESTIONMODELSQL_H

#include <QObject>

#include "../Models/question.h"
#include "selectsql.h"
#include "selectwithcriteriasql.h"
#include "wheresql.h"

class QuestionModelSql : public QObject {
private:
  Q_OBJECT
  Question *_model;

  template <typename T>
  T getQualityFromQuery(QSqlQuery *query, QString coulmnName);
  QString getQStringFromQuery(QSqlQuery *query, QString columnName);

public:
  explicit QuestionModelSql(Question *model, QObject *parent = nullptr);
  Question *selectQuestion(int id);

signals:
};

#endif // QUESTIONMODELSQL_H
