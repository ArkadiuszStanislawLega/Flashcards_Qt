#include "tagandquestionrelationsql.h"

#include <stringmanager.h>

TagAndQuestionRelationSql::TagAndQuestionRelationSql(Tag *tag,
                                                     Question *question,
                                                     QObject *parent)
    : QObject{parent} {
  this->_tag = tag;
  this->_question = question;
}

bool TagAndQuestionRelationSql::isQuestionAndTagValid() {
  if (!this->_tag) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isQuestionAndTagValid -- "
        "poninter to tag is empty.");
  }
  if (!this->_question) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isQuestionAndTagValid -- "
        "pointer to question is empty.");
  }

  if (this->_tag->getId() <= 0) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isQuestionAndTagValid -- "
        "property id in tag is zero or subzero.");
  }

  if (this->_question->getId() <= 0) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isQuestionAndTagValid -- property id in "
        "question is zero or subzero.");
  }
  return true;
}

bool TagAndQuestionRelationSql::isInsertedSql() {
  try {
    if (!isQuestionAndTagValid()) {
      return false;
    }

    InsertSql *sql =
        new InsertSql(StringManager::get(StringID::TableQuestionsTags),
                      {StringManager::get(StringID::ColumnTagId),
                       StringManager::get(StringID::ColumnQuestionId)},
                      this);

    executeQuery<InsertSql>(sql);

  } catch (std::invalid_argument &e) {
    qWarning() << "TagAndQuestionRelationSql::isInsertedSql" << e.what();
    return false;
  }

  return true;
}

bool TagAndQuestionRelationSql::isDeletedSql() {
  try {
    if (!(isQuestionAndTagValid())) {
      return false;
    }
    DeleteSql *sql =
        new DeleteSql(StringManager::get(StringID::TableQuestionsTags),
                      {StringManager::get(StringID::ColumnTagId),
                       StringManager::get(StringID::ColumnQuestionId)},
                      this);

    executeQuery<DeleteSql>(sql);

  } catch (std::invalid_argument &e) {
    qWarning() << this->metaObject()->className() << "::isDeleteSql"
               << e.what();
    return false;
  }
  return true;
}

bool TagAndQuestionRelationSql::isSelectedSql() {
  try {
    if (!isQuestionAndTagValid()) {
      return false;
    }

    FindByKeySql *sql =
        new FindByKeySql(StringManager::get(StringID::TableQuestionsTags),
                         {StringManager::get(StringID::ColumnTagId),
                          StringManager::get(StringID::ColumnQuestionId)},
                         this);

    executeQuery<FindByKeySql>(sql);

  } catch (std::invalid_argument &e) {
    qWarning() << this->metaObject()->className() << "::isDeleteSql"
               << e.what();
    return false;
  }
  return true;
}

bool TagAndQuestionRelationSql::isAlreadyRelated() {
  if (!isQuestionAndTagValid()) {
    return false;
  }
  QString criteria = StringManager::get(StringID::ColumnTagId) +
                     "=:" + StringManager::get(StringID::ColumnTagId) +
                     " AND " + StringManager::get(StringID::ColumnQuestionId) +
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
    QString message = this->metaObject()->className();
    message +=
        "::isAlreadyRelated --" + StringManager::get(StringID::TheQueryFailed);
    throw std::invalid_argument(message.toStdString());
  }
  return query.next();
}

bool TagAndQuestionRelationSql::isAllRelationRemoved() {
  if (!this->_question && !this->_tag) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isAllRelationRemoved -- question and tag "
        "pointers are null.");
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
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isAllRelationRemoved -- the query failed.");
  }
  return true;
}

QList<Tag *> TagAndQuestionRelationSql::getRelatedTags() {
  if (!this->_question) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedTags -- poninter to question "
        "is empty.");
  }

  if (this->_question->getId() <= 0) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedTags -- property id in "
        "question is zero or subzero.");
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
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedTags -- the query failed.");
  }

  while (query.next()) {
    try {
      tags.push_back(FromQueryToTagConverter::get(&query));
      tags.back()->setParent(this);
    } catch (std::invalid_argument &e) {
      qWarning() << this->metaObject()->className() << "::getRelatedTags -- "
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
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedQuestions -- pointer to tag "
        "is empty.");
  }

  if (this->_tag->getId() <= 0) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedQuestions -- property id in "
        "tag is zero or subzero.");
  }

  FindByKeySql *sql =
      new FindByKeySql(StringManager::get(StringID::TableQuestionsTags),
                       {StringManager::get(StringID::ColumnTagId)}, this);

  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnTagId),
                  this->_tag->getId());

  if (!query.exec()) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedTags -- the query failed.");
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
  if (!this->_tag) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedActiveQuesitons -- poninter to "
        "tag is empty.");
  }

  if (this->_tag->getId() <= 0) {
    throw std::invalid_argument("TagAndQuestionRelationSql::"
                                "getRelatedActiveQuesitons -- property id in "
                                "tag is zero or subzero.");
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
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedActiveQuesitons -- the query "
        "failed.");
  }

  while (query.next()) {
    try {
      questions.push_back(FromQueryToQuestionConverter::get(&query));
      questions.back()->setParent(this);
    } catch (std::invalid_argument &e) {
      qWarning() << this->metaObject()->className()
                 << "::getRelatedActiveQuesitons -- " << e.what();
    }
  }

  return questions;
}

template <typename T> void TagAndQuestionRelationSql::executeQuery(T *sql) {
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnTagId),
                  this->_tag->getId());
  query.bindValue(":" + StringManager::get(StringID::ColumnQuestionId),
                  this->_question->getId());

  if (!query.exec()) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isDeleteSql -- the query failed.");
  }
}
