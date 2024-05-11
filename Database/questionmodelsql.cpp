#include "questionmodelsql.h"

#include "deletesql.h"

QuestionModelSql::QuestionModelSql(Question *model, QObject *parent)
    : QObject{parent} {
  this->_model = model;
}

bool QuestionModelSql::isInsertedSql() {
  if (!this->_model) {
    throw std::invalid_argument(
        "QuestionModelSql::isInsertedSql -- pointer to question is null.");
  }
  InsertSql insert = InsertSql(
      TABLE_QUESTIONS, {COLUMN_VALUE, COLUMN_ANSWER, COLUMN_IS_ACTIVE},
      {this->_model->getValue(), this->_model->getAnswer(),
       this->_model->getIsActive() ? "1" : "0"},
      this);

  if (!insert.generate().exec()) {
    throw std::invalid_argument(
        "QuestionModelSql::isInsertSql -- the query failed.");
  }
  this->findByCriteria();
  return true;
}

bool QuestionModelSql::isDeleteSql() {
  if (!this->_model) {
    throw std::invalid_argument(
        "QuestionModelSql::isDeleteSql -- pointer to question is null.");
  }

  if (this->_model->getId() <= 0) {
    throw std::invalid_argument("QuestionModelSql::isDeleteSql -- property id "
                                "of the model is zero or below zero");
  }

  DeleteSql queryS = DeleteSql(TABLE_QUESTIONS, {COLUMN_ID}, this);

  QSqlQuery query;
  query.prepare(queryS.generate());
  query.bindValue(":" + COLUMN_ID, this->_model->getId());

  if (!query.exec()) {
    throw std::invalid_argument(
        "QuestionModelSql::isDeleteSql -- the query failed.");
  }
  return true;
}

Question *QuestionModelSql::selectQuestion(int id) {
  if (id <= 0) {
    throw std::invalid_argument(
        "QuestionModelSql::selectQuestion - property id is zero or subzero.");
  }

  FindByKeySql *sql = new FindByKeySql(TABLE_QUESTIONS, id, {}, this);
  QSqlQuery query = sql->generate();

  if (!query.exec()) {
    throw std::invalid_argument(
        "QuestionSql::selectQuestion - the query failed.");
  }

  this->convertQueryToQuestion(&query);

  return this->_model;
}

Question *QuestionModelSql::findByCriteria() {
  if (this->_model->getValue().isEmpty()) {
    throw std::invalid_argument(
        "QuestionModelSql::selectQuestion -- value is empty.");
  }
  if (this->_model->getAnswer().isEmpty()) {
    throw std::invalid_argument(
        "QuestionModelSql::selectQuestion -- answer is empty.");
  }

  QString criteria = COLUMN_VALUE + "=:" + COLUMN_VALUE + " " + AND +
                     COLUMN_ANSWER + "=:" + COLUMN_ANSWER;

  SelectWithCriteriaSql select =
      SelectWithCriteriaSql(TABLE_QUESTIONS, {}, criteria, this);

  QSqlQuery query;
  query.prepare(select.generate());
  query.bindValue(":" + COLUMN_VALUE, this->_model->getValue());
  query.bindValue(":" + COLUMN_ANSWER, this->_model->getAnswer());

  if (!query.exec()) {
    throw std::invalid_argument(
        "QuestionModelSql::findByCriteria - the query failed.");
  }

  if (!query.next()) {
    throw std::invalid_argument(
        "QuestionModelSql::findByCriteria - can't find question in database.");
  }

  this->convertQueryToQuestion(&query);

  return this->_model;
}

void QuestionModelSql::convertQueryToQuestion(QSqlQuery *query) {
  this->_model->setId(QueryToValueConverter::get<int>(query, COLUMN_ID));
  this->_model->setAnswer(
      QueryToValueConverter::get<QString>(query, COLUMN_ANSWER));
  this->_model->setValue(
      QueryToValueConverter::get<QString>(query, COLUMN_VALUE));
  this->_model->setIsActive(
      QueryToValueConverter::get<bool>(query, COLUMN_IS_ACTIVE));
}
