#include "questionmodelsql.h"

#include <stringmanager.h>

#include <Exceptions/nullpointertoquestionexception.h>

QuestionModelSql::QuestionModelSql(Question *model, QObject *parent)
    : QObject{parent} {
  this->_model = model;
}

bool QuestionModelSql::isInsertedSql() {
  if (!this->_model) {
    throw new NullPointerToQuestionException(this->metaObject()->className(),
                                             "::isInsertedSql --");
  }
  InsertSql insert = InsertSql(StringManager::get(StringID::TableQuestions),
                               {StringManager::get(StringID::ColumnValue),
                                StringManager::get(StringID::ColumnAnswer),
                                StringManager::get(StringID::ColumnIsActive)},
                               this);

  QSqlQuery query;
  query.prepare(insert.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnValue),
                  this->_model->getValue());
  query.bindValue(":" + StringManager::get(StringID::ColumnAnswer),
                  this->_model->getAnswer());
  query.bindValue(":" + StringManager::get(StringID::ColumnIsActive),
                  this->_model->getIsActive());

  if (!query.exec()) {

    QString message = this->metaObject()->className();
    message += "::isInsertedSql --";
    message += StringManager::get(StringID::ErrorQueryFailed);
    throw std::invalid_argument(message.toStdString());
  }
  this->findByCriteria();
  return true;
}

bool QuestionModelSql::isDeleteSql() {
  if (!this->_model) {
    QString message = this->metaObject()->className();
    message += "::isDeleteSql --";
    message += StringManager::get(StringID::ErrorPointerToQuestionEmpty);
    throw std::invalid_argument(message.toStdString());
  }

  if (this->_model->getId() <= 0) {
    QString message = this->metaObject()->className();
    message += "::isDeleteSql --";
    message += StringManager::get(StringID::ErrorPropertyIdInQuestionZero);
    throw std::invalid_argument(message.toStdString());
  }
  DeleteSql queryS = DeleteSql(StringManager::get(StringID::TableQuestions),
                               {StringManager::get(StringID::ColumnId)}, this);

  QSqlQuery query;
  query.prepare(queryS.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId),
                  this->_model->getId());

  if (!query.exec()) {
    QString message = this->metaObject()->className();
    message += "::isDeleteSql --";
    message += StringManager::get(StringID::ErrorQueryFailed);
    throw std::invalid_argument(message.toStdString());
  }
  return true;
}

Question *QuestionModelSql::selectQuestion(int id) {
  if (id <= 0) {
    QString message = this->metaObject()->className();
    message += "::selectQuestion --";
    message += StringManager::get(StringID::ErrorPropertyIdInQuestionZero);
    throw std::invalid_argument(message.toStdString());
  }

  FindByKeySql *sql =
      new FindByKeySql(StringManager::get(StringID::TableQuestions), {}, this);
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId), id);

  if (!query.exec()) {
    QString message = this->metaObject()->className();
    message += "::selectQuestion --";
    message += StringManager::get(StringID::ErrorQueryFailed);
    throw std::invalid_argument(message.toStdString());
  }

  this->convertQueryToQuestion(&query);

  return this->_model;
}

Question *QuestionModelSql::findByCriteria() {
  if (this->_model->getValue().isEmpty()) {
    QString message = this->metaObject()->className();
    message += "::findByCriteria --";
    message += StringManager::get(StringID::ErrorPropertyValueIsEmpty);
    throw std::invalid_argument(message.toStdString());
  }
  if (this->_model->getAnswer().isEmpty()) {
    QString message = this->metaObject()->className();
    message += "::findByCriteria --";
    message += StringManager::get(StringID::ErrorPropertyAnswerIsEmpty);
    throw std::invalid_argument(message.toStdString());
  }

  QString criteria = StringManager::get(StringID::ColumnValue) +
                     "=:" + StringManager::get(StringID::ColumnValue) + " " +
                     AND + StringManager::get(StringID::ColumnAnswer) +
                     "=:" + StringManager::get(StringID::ColumnAnswer);

  SelectWithCriteriaSql select = SelectWithCriteriaSql(
      StringManager::get(StringID::TableQuestions), {}, criteria, this);

  QSqlQuery query;
  query.prepare(select.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnValue),
                  this->_model->getValue());
  query.bindValue(":" + StringManager::get(StringID::ColumnAnswer),
                  this->_model->getAnswer());

  if (!query.exec()) {
    QString message = this->metaObject()->className();
    message += "::findByCriteria --";
    message += StringManager::get(StringID::ErrorQueryFailed);
    throw std::invalid_argument(message.toStdString());
  }

  if (!query.next()) {
    QString message = this->metaObject()->className();
    message += "::findByCriteria --";
    message += StringManager::get(StringID::ErrorCantFindQuestion);
    throw std::invalid_argument(message.toStdString());
  }

  this->convertQueryToQuestion(&query);

  return this->_model;
}

bool QuestionModelSql::updateSql() {
  if (!this->_model) {
    QString message = this->metaObject()->className();
    message += "::updateSql --";
    message += StringManager::get(StringID::ErrorPointerToQuestionEmpty);
    throw std::invalid_argument(message.toStdString());
  }

  if (this->_model->getId() <= 0) {
    QString message = this->metaObject()->className();
    message += "::updateSql --";
    message += StringManager::get(StringID::ErrorPropertyIdInQuestionZero);
    throw std::invalid_argument(message.toStdString());
  }

  UpdateSql sql = UpdateSql(StringManager::get(StringID::TableQuestions),
                            {StringManager::get(StringID::ColumnValue),
                             StringManager::get(StringID::ColumnAnswer),
                             StringManager::get(StringID::ColumnIsActive)},
                            this);

  QSqlQuery query;
  query.prepare(sql.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId),
                  this->_model->getId());
  query.bindValue(":" + StringManager::get(StringID::ColumnValue),
                  this->_model->getValue());
  query.bindValue(":" + StringManager::get(StringID::ColumnAnswer),
                  this->_model->getAnswer());
  query.bindValue(":" + StringManager::get(StringID::ColumnIsActive),
                  this->_model->getIsActive());
  qDebug() << query.lastQuery();

  if (!query.exec()) {
    QString message = this->metaObject()->className();
    message += "::updateSql --";
    message += StringManager::get(StringID::ErrorQueryFailed);
    throw std::invalid_argument(message.toStdString());
  }

  return true;
}

void QuestionModelSql::convertQueryToQuestion(QSqlQuery *query) {
  this->_model->setId(FromQueryToValueConverter::get<int>(
      query, StringManager::get(StringID::ColumnId)));
  this->_model->setAnswer(FromQueryToValueConverter::get<QString>(
      query, StringManager::get(StringID::ColumnAnswer)));
  this->_model->setValue(FromQueryToValueConverter::get<QString>(
      query, StringManager::get(StringID::ColumnValue)));
  this->_model->setIsActive(FromQueryToValueConverter::get<bool>(
      query, StringManager::get(StringID::ColumnIsActive)));
}
