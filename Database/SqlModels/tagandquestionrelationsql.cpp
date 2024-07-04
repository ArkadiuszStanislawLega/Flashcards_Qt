#include "tagandquestionrelationsql.h"

#include <stringmanager.h>

#include <Exceptions/belowzeroidexception.h>
#include <Exceptions/nullpointertoquestionandtagexception.h>
#include <Exceptions/nullpointertoquestionexception.h>
#include <Exceptions/nullpointertotagexception.h>
#include <Exceptions/queryfiledexception.h>

TagAndQuestionRelationSql::TagAndQuestionRelationSql(Tag *tag,
                                                     Question *question,
                                                     QObject *parent)
    : QObject{parent} {
  this->_tag = tag;
  this->_question = question;
}

bool TagAndQuestionRelationSql::isQuestionAndTagValid(const char *methodName) {
  if (!this->_tag) {
    throw NullPointerToTagException(this->metaObject()->className(),
                                    methodName);
  }

  if (!this->_question) {
    throw NullPointerToQuestionException(this->metaObject()->className(),
                                         methodName);
  }

  if (this->_tag->getId() <= 0 || this->_question->getId() <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  return true;
}

bool TagAndQuestionRelationSql::isInsertedSql() {
  const char *methodName = "isInsertedSl";
  try {
    if (!isQuestionAndTagValid(methodName)) {
      return false;
    }

    InsertSql *sql =
        new InsertSql(StringManager::get(StringID::TableQuestionsTags),
                      {StringManager::get(StringID::ColumnTagId),
                       StringManager::get(StringID::ColumnQuestionId)},
                      this);

    executeQuery<InsertSql>(sql);
    return true;

  } catch (NullPointerToTagException &e) {
    qWarning() << e.what();
  } catch (NullPointerToQuestionException &e) {
    qWarning() << e.what();
  } catch (BelowZeroIdException &e) {
    qWarning() << e.what();
  }

  return false;
}

bool TagAndQuestionRelationSql::isDeletedSql() {
  const char *methodName = "isDeletedSql";
  try {
    if (!(isQuestionAndTagValid(methodName))) {
      return false;
    }
    DeleteSql *sql =
        new DeleteSql(StringManager::get(StringID::TableQuestionsTags),
                      {StringManager::get(StringID::ColumnTagId),
                       StringManager::get(StringID::ColumnQuestionId)},
                      this);

    executeQuery<DeleteSql>(sql);
    return true;

  } catch (NullPointerToTagException &e) {
    qWarning() << e.what();
  } catch (NullPointerToQuestionException &e) {
    qWarning() << e.what();
  } catch (BelowZeroIdException &e) {
    qWarning() << e.what();
  }
  return false;
}

bool TagAndQuestionRelationSql::isSelectedSql() {
  const char *methodName = "isSelectedSql";
  try {
    if (!isQuestionAndTagValid(methodName)) {
      return false;
    }

    FindByKeySql *sql =
        new FindByKeySql(StringManager::get(StringID::TableQuestionsTags),
                         {StringManager::get(StringID::ColumnTagId),
                          StringManager::get(StringID::ColumnQuestionId)},
                         this);

    executeQuery<FindByKeySql>(sql);
    return true;

  } catch (NullPointerToTagException &e) {
    qWarning() << e.what();
  } catch (NullPointerToQuestionException &e) {
    qWarning() << e.what();
  } catch (BelowZeroIdException &e) {
    qWarning() << e.what();
  }

  return false;
}

bool TagAndQuestionRelationSql::isAlreadyRelated() {
  const char *methodName = "isAlreadyRelated";
  try {
    if (!isQuestionAndTagValid(methodName)) {
      return false;
    }
    QString criteria = StringManager::get(StringID::ColumnTagId) +
                       "=:" + StringManager::get(StringID::ColumnTagId) +
                       " AND " +
                       StringManager::get(StringID::ColumnQuestionId) +
                       "=:" + StringManager::get(StringID::ColumnQuestionId);
    SelectWithCriteriaSql *sql = new SelectWithCriteriaSql(
        StringManager::get(StringID::TableQuestionsTags), {}, criteria, this);

    QSqlQuery query;
    query.prepare(sql->generate());
    query.bindValue(":" + StringManager::get(StringID::ColumnTagId),
                    this->_tag->getId());
    query.bindValue(":" + StringManager::get(StringID::ColumnQuestionId),
                    this->_question->getId());

    if (!query.exec()) {
      throw QueryFiledException(this->metaObject()->className(), methodName);
    }
    return query.next();

  } catch (NullPointerToTagException &e) {
    qWarning() << e.what();
  } catch (NullPointerToQuestionException &e) {
    qWarning() << e.what();
  } catch (BelowZeroIdException &e) {
    qWarning() << e.what();
  }
  return false;
}

bool TagAndQuestionRelationSql::isAllRelationRemoved() {
  const char *methodName = "isAllRelationRemoved";
  if (!this->_question && !this->_tag) {
    throw NullPointerToQuestionAndTagException(this->metaObject()->className(),
                                               methodName);
  }

  QSqlQuery query;

  if (this->_tag && this->_tag->getId()) {
    DeleteSql sql =
        DeleteSql(StringManager::get(StringID::TableQuestionsTags),
                  {StringManager::get(StringID::ColumnTagId)}, this);
    query.prepare(sql.generate());
    query.bindValue(":" + StringManager::get(StringID::ColumnTagId),
                    this->_tag->getId());
  } else if (this->_question && this->_question->getId()) {
    DeleteSql sql =
        DeleteSql(StringManager::get(StringID::TableQuestionsTags),
                  {StringManager::get(StringID::ColumnQuestionId)}, this);
    query.prepare(sql.generate());
    query.bindValue(":" + StringManager::get(StringID::ColumnQuestionId),
                    this->_question->getId());
  }

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }
  return true;
}

QList<Tag *> TagAndQuestionRelationSql::getRelatedTags() {
  const char *methodName = "getRelatedTags";
  if (!this->_question) {
    throw NullPointerToQuestionException(this->metaObject()->className(),
                                         methodName);
  }

  if (this->_question->getId() <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  QList<Tag *> tags;

  QList<QString> requriedFields = {
      StringManager::get(StringID::TableTags) + "." +
          StringManager::get(StringID::ColumnId),
      StringManager::get(StringID::TableTags) + "." +
          StringManager::get(StringID::ColumnTag)};

  QList<std::pair<QString, QString>> connectedTables = {
      {StringManager::get(StringID::TableQuestionsTags),
       StringManager::get(StringID::TableTags)},
      {StringManager::get(StringID::TableQuestions),
       StringManager::get(StringID::TableQuestionsTags)}};

  QList<std::pair<QString, QString>> connectedValues = {
      {StringManager::get(StringID::ColumnTagId),
       StringManager::get(StringID::ColumnId)},
      {StringManager::get(StringID::ColumnId),
       StringManager::get(StringID::ColumnQuestionId)}};

  QString criteria = StringManager::get(StringID::TableQuestionsTags) + "." +
                     StringManager::get(StringID::ColumnQuestionId) +
                     "=:" + StringManager::get(StringID::ColumnQuestionId);

  SelectWithJoinSql *sql = new SelectWithJoinSql(
      StringManager::get(StringID::TableTags), requriedFields, connectedTables,
      connectedValues, criteria, this);

  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnQuestionId),
                  this->_question->getId());

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }

  while (query.next()) {
    try {
      tags.push_back(FromQueryToTagConverter::get(&query));
      tags.back()->setParent(this);
    } catch (std::invalid_argument &e) {
      qWarning() << this->metaObject()->className() << "::" << methodName
                 << e.what();
    }
  }

  return tags;
}

QList<Question *> TagAndQuestionRelationSql::getRelatedQuestions() {
  throw std::invalid_argument("TagAndQuestionRelationSql::getRelatedQuestions "
                              "-- NOT IMPLEMENTED YET!!!!");

  QList<Question *> questions;

  if (!this->_tag) {
    QString message = this->metaObject()->className();
    message += "::getRelatedQuestions --";
    message += StringManager::get(StringID::ErrorPointerToTagAndQuestionEmpty);
    throw std::invalid_argument(message.toStdString());
  }

  if (this->_tag->getId() <= 0) {
    QString message = this->metaObject()->className();
    message += "::getRelatedQuestions --";
    message += StringManager::get(StringID::ErrorPropertyIdInTagZero);
    throw std::invalid_argument(message.toStdString());
  }

  FindByKeySql *sql =
      new FindByKeySql(StringManager::get(StringID::TableQuestionsTags),
                       {StringManager::get(StringID::ColumnTagId)}, this);

  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnTagId),
                  this->_tag->getId());

  if (!query.exec()) {
    QString message = this->metaObject()->className();
    message += "::getRelatedQuestions --";
    message += StringManager::get(StringID::ErrorQueryFailed);
    throw std::invalid_argument(message.toStdString());
  }

  while (query.next()) {
    try {
      questions.push_back(FromQueryToQuestionConverter::get(&query));
      questions.back()->setTags(getRelatedTags());
      questions.back()->setParent(this);
    } catch (std::invalid_argument &e) {
      qWarning() << this->metaObject()->className()
                 << "::getRelatedQuestions -- " << e.what();
    }
  }

  return questions;
}

QList<Question *> TagAndQuestionRelationSql::getRelatedActiveQuesitons() {
  const char *methodName = "getRelatedActiveQuesitons";
  if (!this->_tag) {
    throw NullPointerToTagException(this->metaObject()->className(),
                                    methodName);
  }

  if (this->_tag->getId() <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  QList<Question *> questions;

  QList<QString> requriedFields = {
      StringManager::get(StringID::TableQuestions) + "." +
          StringManager::get(StringID::ColumnId),
      StringManager::get(StringID::TableQuestions) + "." +
          StringManager::get(StringID::ColumnValue),
      StringManager::get(StringID::TableQuestions) + "." +
          StringManager::get(StringID::ColumnAnswer),
      StringManager::get(StringID::TableQuestions) + "." +
          StringManager::get(StringID::ColumnIsActive)};

  QList<std::pair<QString, QString>> connectedTables = {
      {StringManager::get(StringID::TableQuestionsTags),
       StringManager::get(StringID::TableQuestions)},
      {StringManager::get(StringID::TableTags),
       StringManager::get(StringID::TableQuestionsTags)}};

  QList<std::pair<QString, QString>> connectedValues = {
      {StringManager::get(StringID::ColumnQuestionId),
       StringManager::get(StringID::ColumnId)},
      {StringManager::get(StringID::ColumnId),
       StringManager::get(StringID::ColumnTagId)}};

  QString criteria = StringManager::get(StringID::TableQuestionsTags) + "." +
                     StringManager::get(StringID::ColumnTagId) +
                     "=:" + StringManager::get(StringID::ColumnId) + " AND " +
                     StringManager::get(StringID::TableQuestions) + "." +
                     StringManager::get(StringID::ColumnIsActive) + "=1 " +
                     ORDER_BY + StringManager::get(StringID::TableQuestions) +
                     "." + StringManager::get(StringID::ColumnValue);

  SelectWithJoinSql *sql = new SelectWithJoinSql(
      StringManager::get(StringID::TableQuestions), requriedFields,
      connectedTables, connectedValues, criteria, this);

  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId),
                  this->_tag->getId());

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }

  while (query.next()) {
    try {
      questions.push_back(FromQueryToQuestionConverter::get(&query));
      questions.back()->setParent(this);
    } catch (std::invalid_argument &e) {
      qWarning() << this->metaObject()->className() << "::" << methodName
                 << e.what();
    }
  }

  return questions;
}

template <typename T> void TagAndQuestionRelationSql::executeQuery(T *sql) {
  const char *methodName = "executeQuery";
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnTagId),
                  this->_tag->getId());
  query.bindValue(":" + StringManager::get(StringID::ColumnQuestionId),
                  this->_question->getId());

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }
}
