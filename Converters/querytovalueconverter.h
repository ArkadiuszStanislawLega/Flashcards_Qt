#ifndef QUERYTOVALUECONVERTER_H
#define QUERYTOVALUECONVERTER_H

#include "qsqlrecord.h"
#include <QSqlQuery>

class QueryToValueConverter {
public:
  template <typename T> static T get(QSqlQuery *query, QString columnName) {
    if (!query) {
      throw std::invalid_argument("Query is empty.");
    }

    if (columnName.isEmpty()) {
      throw std::invalid_argument("Colmun name is empty.");
    }

    int columnIndex = query->record().indexOf(columnName);

    if constexpr (std::is_same_v<T, int>) {
      return query->value(columnIndex).toInt();
    }

    if constexpr (std::is_same_v<T, bool>) {
      return query->value(columnIndex).toBool();
    };

    if constexpr (std::is_same_v<T, QString>) {
      return query->value(columnIndex).toString();
    };
  }
};

#endif // QUERYTOVALUECONVERTER_H
