#include "fromquerytotagconverter.h"

#include <stringmanager.h>

Tag *FromQueryToTagConverter::get(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument(
        "FromQueryToQuestionConverter::get -- pointer to query is empty.");
  }
  try {
    return new Tag(FromQueryToValueConverter::get<int>(
                       query, StringManager::get(StringID::ColumnId)),
                   FromQueryToValueConverter::get<QString>(
                       query, StringManager::get(StringID::ColumnTag)));
  } catch (std::invalid_argument &e) {
    qWarning() << "FromQueryToQuestionConverter::get" << e.what();
  }
  return new Tag();
}
