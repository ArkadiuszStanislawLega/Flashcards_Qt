#include "fromquerytotagconverter.h"

Tag *FromQueryToTagConverter::get(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument(
        "FromQueryToQuestionConverter::get -- pointer to query is empty.");
  }
  try {
    return new Tag(QueryToValueConverter::get<int>(query, COLUMN_ID),
                   QueryToValueConverter::get<QString>(query, COLUMN_TAG));
  } catch (std::invalid_argument &e) {
    qWarning() << "FromQueryToQuestionConverter::get" << e.what();
  }
  return new Tag();
}
