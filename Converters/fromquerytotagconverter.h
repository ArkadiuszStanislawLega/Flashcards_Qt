#ifndef FROMQUERYTOTAGCONVERTER_H
#define FROMQUERYTOTAGCONVERTER_H

#include "../Models/tag.h"
#include "fromquerytovalueconverter.h"
#include <QSqlQuery>

class FromQueryToTagConverter {
public:
  static Tag *get(QSqlQuery *);
};

#endif // FROMQUERYTOTAGCONVERTER_H
