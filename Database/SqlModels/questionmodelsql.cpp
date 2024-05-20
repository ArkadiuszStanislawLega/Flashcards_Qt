#include "questionmodelsql.h"

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
      TABLE_QUESTIONS, {COLUMN_VALUE, COLUMN_ANSWER, COLUMN_IS_ACTIVE}, this);

  QSqlQuery query;
  query.prepare(insert.generate());
  query.bindValue(":" + COLUMN_VALUE, this->_model->getValue());
  query.bindValue(":" + COLUMN_ANSWER, this->_model->getAnswer());
  query.bindValue(":" + COLUMN_IS_ACTIVE, this->_model->getIsActive());

  if (!query.exec()) {
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

  FindByKeySql *sql = new FindByKeySql(TABLE_QUESTIONS, {}, this);
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + COLUMN_ID, id);

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

bool QuestionModelSql::updateSql() {
  if (!this->_model) {
    throw std::invalid_argument(
        "QuestionModelSql::updateSql -- question reference is empty.");
  }

  if (this->_model->getId() <= 0) {
    throw std::invalid_argument("QuestionModelSql::updateSql -- property id in "
                                "question is zero or subzero.");
  }

  UpdateSql sql = UpdateSql(
      TABLE_QUESTIONS, {COLUMN_VALUE, COLUMN_ANSWER, COLUMN_IS_ACTIVE}, this);

  QSqlQuery query;
  query.prepare(sql.generate());
  query.bindValue(":" + COLUMN_ID, this->_model->getId());
  query.bindValue(":" + COLUMN_VALUE, this->_model->getValue());
  query.bindValue(":" + COLUMN_ANSWER, this->_model->getAnswer());
  query.bindValue(":" + COLUMN_IS_ACTIVE, this->_model->getIsActive());
  qDebug() << query.lastQuery();

  if (!query.exec()) {
    throw std::invalid_argument(
        "QuestionModelSql::updateSql -- query does not execute.");
  }

  return true;
}

void QuestionModelSql::convertQueryToQuestion(QSqlQuery *query) {
  this->_model->setId(FromQueryToValueConverter::get<int>(query, COLUMN_ID));
  this->_model->setAnswer(
      FromQueryToValueConverter::get<QString>(query, COLUMN_ANSWER));
  this->_model->setValue(
      FromQueryToValueConverter::get<QString>(query, COLUMN_VALUE));
  this->_model->setIsActive(
      FromQueryToValueConverter::get<bool>(query, COLUMN_IS_ACTIVE));
}