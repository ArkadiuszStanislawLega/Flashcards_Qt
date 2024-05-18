#include "tagandquestionrelationsql.h"

#include "deletesql.h"
#include "findbykeysql.h"
#include "insertsql.h"
#include "selectsql.h"
#include "selectwithcriteriasql.h"
#include "selectwithjoinsql.h"

#include <Converters/fromquerytoquestionconverter.h>
#include <Converters/fromquerytotagconverter.h>
#include <Converters/fromquerytovalueconverter.h>

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

    InsertSql *sql = new InsertSql(TABLE_QUESTIONS_TAGS,
                                   {COLUMN_TAG_ID, COLUMN_QUESTION_ID}, this);

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
    DeleteSql *sql = new DeleteSql(TABLE_QUESTIONS_TAGS,
                                   {COLUMN_TAG_ID, COLUMN_QUESTION_ID}, this);

    executeQuery<DeleteSql>(sql);

  } catch (std::invalid_argument &e) {
    qWarning() << "TagAndQuestionRelationSql::isDeleteSql" << e.what();
    return false;
  }
  return true;
}

bool TagAndQuestionRelationSql::isSelectedSql() {
  try {
    if (!isQuestionAndTagValid()) {
      return false;
    }

    FindByKeySql *sql = new FindByKeySql(
        TABLE_QUESTIONS_TAGS, {COLUMN_TAG_ID, COLUMN_QUESTION_ID}, this);

    executeQuery<FindByKeySql>(sql);

  } catch (std::invalid_argument &e) {
    qWarning() << "TagAndQuestionRelationSql::isDeleteSql" << e.what();
    return false;
  }
  return true;
}

bool TagAndQuestionRelationSql::isAllRelationRemoved() {
  if (!this->_question && !this->_tag) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isAllRelationRemoved -- question and tag "
        "pointers are null.");
  }

  if (this->_question->getId() <= 0 && this->_tag->getId() <= 0) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isAllRelationRemoved -- proprety id in "
        "question and tag are zero or subzero.");
  }

  QSqlQuery query;

  if (this->_tag->getId()) {
    DeleteSql sql = DeleteSql(TABLE_QUESTIONS_TAGS, {COLUMN_TAG_ID}, this);
    query.prepare(sql.generate());
    query.bindValue(":" + COLUMN_TAG_ID, this->_tag->getId());
  } else {
    DeleteSql sql = DeleteSql(TABLE_QUESTIONS_TAGS, {COLUMN_QUESTION_ID}, this);
    query.prepare(sql.generate());
    query.bindValue(":" + COLUMN_QUESTION_ID, this->_question->getId());
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

  QList<QString> requriedFields = {TABLE_TAGS + "." + COLUMN_ID,
                                   TABLE_TAGS + "." + COLUMN_TAG};

  QList<std::pair<QString, QString>> connectedTables = {
      {TABLE_QUESTIONS_TAGS, TABLE_TAGS},
      {TABLE_QUESTIONS, TABLE_QUESTIONS_TAGS}};

  QList<std::pair<QString, QString>> connectedValues = {
      {COLUMN_TAG_ID, COLUMN_ID}, {COLUMN_ID, COLUMN_QUESTION_ID}};

  QString criteria = TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID +
                     "=:" + COLUMN_QUESTION_ID;

  SelectWithJoinSql *sql =
      new SelectWithJoinSql(TABLE_TAGS, requriedFields, connectedTables,
                            connectedValues, criteria, this);

  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + COLUMN_QUESTION_ID, this->_question->getId());

  if (!query.exec()) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::getRelatedTags -- the query failed.");
  }

  while (query.next()) {
    try {
      tags.push_back(FromQueryToTagConverter::get(&query));
      tags.back()->setParent(this);
    } catch (std::invalid_argument &e) {
      qWarning() << "TagAndQuestionRelationSql::getRelatedTags -- " << e.what();
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
      new FindByKeySql(TABLE_QUESTIONS_TAGS, {COLUMN_TAG_ID}, this);

  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + COLUMN_TAG_ID, this->_tag->getId());

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
      qWarning() << "TagAndQuestionRelationSql::getRelatedQuestions -- "
                 << e.what();
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

  QList<QString> requriedFields = {TABLE_QUESTIONS + "." + COLUMN_ID,
                                   TABLE_QUESTIONS + "." + COLUMN_VALUE,
                                   TABLE_QUESTIONS + "." + COLUMN_ANSWER,
                                   TABLE_QUESTIONS + "." + COLUMN_IS_ACTIVE};

  QList<std::pair<QString, QString>> connectedTables = {
      {TABLE_QUESTIONS_TAGS, TABLE_QUESTIONS},
      {TABLE_TAGS, TABLE_QUESTIONS_TAGS}};

  QList<std::pair<QString, QString>> connectedValues = {
      {COLUMN_QUESTION_ID, COLUMN_ID}, {COLUMN_ID, COLUMN_TAG_ID}};

  QString criteria = TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID +
                     "=:" + COLUMN_ID + " AND " + TABLE_QUESTIONS + "." +
                     COLUMN_IS_ACTIVE + "=1 " + ORDER_BY + TABLE_QUESTIONS +
                     "." + COLUMN_VALUE;

  SelectWithJoinSql *sql =
      new SelectWithJoinSql(TABLE_QUESTIONS, requriedFields, connectedTables,
                            connectedValues, criteria, this);

  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + COLUMN_ID, this->_tag->getId());

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
      qWarning() << "TagAndQuestionRelationSql::getRelatedActiveQuesitons -- "
                 << e.what();
    }
  }

  return questions;
}

template <typename T> void TagAndQuestionRelationSql::executeQuery(T *sql) {
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + COLUMN_TAG_ID, this->_tag->getId());
  query.bindValue(":" + COLUMN_QUESTION_ID, this->_question->getId());

  qDebug() << query.lastQuery();

  if (!query.exec()) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isDeleteSql -- the query failed.");
  }
}
