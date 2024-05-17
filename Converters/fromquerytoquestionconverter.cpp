#include "fromquerytoquestionconverter.h"

Question *FromQueryToQuestionConverter::get(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument(
        "FromQueryToQuestionConverter::get -- pointer to query is empty.");
  }

  try {
    return new Question(
        FromQueryToValueConverter::get<int>(query, COLUMN_ID),
        FromQueryToValueConverter::get<QString>(query, COLUMN_ANSWER),
        FromQueryToValueConverter::get<QString>(query, COLUMN_VALUE),
        FromQueryToValueConverter::get<bool>(query, COLUMN_IS_ACTIVE), {});
  } catch (std::invalid_argument &e) {
    qWarning() << "FromQueryToQuestionConverter::get" << e.what();
  }
  return new Question();
}
