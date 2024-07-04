#include "questionmodelsql.h"

#include <Exceptions/answerisemptyexception.h>
#include <Exceptions/cantfindquestionexception.h>
#include <Exceptions/valueisemptyexception.h>

QuestionModelSql::QuestionModelSql(Question *model, QObject *parent)
    : QObject{parent} {
  this->_model = model;
}

bool QuestionModelSql::isInsertedSql() {
  const char *methodName = "isInsertedSql";
  if (!this->_model) {
    throw NullPointerToQuestionException(this->metaObject()->className(),
                                         methodName);
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
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }
  try {
    this->findByCriteria();
  } catch (ValueIsEmptyException &e) {
    qWarning() << this->metaObject()->className() << methodName << e.what();
    return false;
  } catch (AnswerIsEmptyException &e) {
    qWarning() << this->metaObject()->className() << methodName << e.what();
    return false;
  } catch (QueryFiledException &e) {
    qWarning() << this->metaObject()->className() << methodName << e.what();
    return false;
  } catch (CantFindQuestionException &e) {
    qWarning() << this->metaObject()->className() << methodName << e.what();
    return false;
  }

  return true;
}

bool QuestionModelSql::isDeleteSql() {
  const char *methodName = "isDeleteSql";

  if (!this->_model) {
    throw NullPointerToQuestionException(this->metaObject()->className(),
                                         methodName);
  }

  if (this->_model->getId() <= 0) {
    throw new BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  DeleteSql queryS = DeleteSql(StringManager::get(StringID::TableQuestions),
                               {StringManager::get(StringID::ColumnId)}, this);

  QSqlQuery query;
  query.prepare(queryS.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId),
                  this->_model->getId());

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }
  return true;
}

Question *QuestionModelSql::selectQuestion(int id) {
  const char *methodName = "selectQuestion";

  if (id <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  FindByKeySql *sql =
      new FindByKeySql(StringManager::get(StringID::TableQuestions), {}, this);
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId), id);

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }

  this->convertQueryToQuestion(&query);

  return this->_model;
}

Question *QuestionModelSql::findByCriteria() {
  const char *methodName = "findByCriteria";

  if (this->_model->getValue().isEmpty()) {
    throw ValueIsEmptyException(this->metaObject()->className(), methodName);
  }

  if (this->_model->getAnswer().isEmpty()) {
    throw AnswerIsEmptyException(this->metaObject()->className(), methodName);
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
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }

  if (!query.next()) {
    throw CantFindQuestionException(this->metaObject()->className(),
                                    methodName);
  }

  this->convertQueryToQuestion(&query);

  return this->_model;
}

bool QuestionModelSql::updateSql() {
  const char *methodName = "updateSql";
  if (!this->_model) {
    throw NullPointerToQuestionException(this->metaObject()->className(),
                                         methodName);
  }

  if (this->_model->getId() <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
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
    throw QueryFiledException(this->metaObject()->className(), methodName);
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
