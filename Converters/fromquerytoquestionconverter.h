#ifndef FROMQUERYTOQUESTIONCONVERTER_H
#define FROMQUERYTOQUESTIONCONVERTER_H

#include "Models/question.h"
#include "qsqlquery.h"
#include "querytovalueconverter.h"

class FromQueryToQuestionConverter {
public:
  static Question *get(QSqlQuery *);
};

#endif // FROMQUERYTOQUESTIONCONVERTER_H
