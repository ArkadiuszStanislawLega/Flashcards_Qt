#include "fromquerytoquestionconverter.h"

Question *FromQueryToQuestionConverter::get(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument(
        "FromQueryToQuestionConverter::get -- pointer to query is empty.");
  }

  try {
    return new Question(
        QueryToValueConverter::get<int>(query, COLUMN_ID),
        QueryToValueConverter::get<QString>(query, COLUMN_ANSWER),
        QueryToValueConverter::get<QString>(query, COLUMN_VALUE),
        QueryToValueConverter::get<bool>(query, COLUMN_IS_ACTIVE), {});
  } catch (std::invalid_argument &e) {
    qWarning() << "FromQueryToQuestionConverter::get" << e.what();
  }
  return new Question();
}
