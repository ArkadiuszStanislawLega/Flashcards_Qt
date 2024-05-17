#ifndef FROMQUERYTOQUESTIONCONVERTER_H
#define FROMQUERYTOQUESTIONCONVERTER_H

#include "Models/question.h"
#include "qsqlquery.h"
#include "fromquerytovalueconverter.h"

class FromQueryToQuestionConverter {
public:
  static Question *get(QSqlQuery *);
};

#endif // FROMQUERYTOQUESTIONCONVERTER_H
