#ifndef QUESTIONMODELSQL_H
#define QUESTIONMODELSQL_H

#include <QObject>

#include "../Converters/querytovalueconverter.h"
#include "../Models/question.h"
#include "selectsql.h"
#include "selectwithcriteriasql.h"
#include "wheresql.h"

class QuestionModelSql : public QObject {
private:
  Q_OBJECT
  Question *_model;

  template <class T>
  T getQualityFromQuery(QSqlQuery *query, QString coulmnName);

public:
  explicit QuestionModelSql(Question *model, QObject *parent = nullptr);
  Question *selectQuestion(int id);

signals:
};

#endif // QUESTIONMODELSQL_H