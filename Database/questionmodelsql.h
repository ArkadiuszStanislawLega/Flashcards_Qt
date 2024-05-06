#ifndef QUESTIONMODELSQL_H
#define QUESTIONMODELSQL_H

#include "../Models/question.h"
#include "selectsql.h"
#include "wheresql.h"
#include <QObject>

class QuestionModelSql : public QObject {
private:
  Q_OBJECT
  Question *_model;

  template <typename T>
  T getQualityFromQuery(QSqlQuery *query, QString coulmnName);
  QString getQStringFromQuery(QSqlQuery *query, QString columnName);

public:
  explicit QuestionModelSql(Question *model, QObject *parent = nullptr);
  Question *selectQuesiton(int id);

signals:
};

#endif // QUESTIONMODELSQL_H
