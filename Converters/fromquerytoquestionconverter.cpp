#include "fromquerytoquestionconverter.h"

#include <stringmanager.h>

Question *FromQueryToQuestionConverter::get(QSqlQuery *query) {
  assert(query);

  try {
    return new Question(
        FromQueryToValueConverter::get<int>(
            query, StringManager::get(StringID::ColumnId)),
        FromQueryToValueConverter::get<QString>(
            query, StringManager::get(StringID::ColumnValue)),
        FromQueryToValueConverter::get<QString>(
            query, StringManager::get(StringID::ColumnAnswer)),
        FromQueryToValueConverter::get<bool>(
            query, StringManager::get(StringID::ColumnIsActive)),
        {});
  } catch (std::invalid_argument &e) {
    qWarning() << "FromQueryToQuestionConverter::get" << e.what();
  }
  return new Question();
}
