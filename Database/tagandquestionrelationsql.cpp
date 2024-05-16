#include "tagandquestionrelationsql.h"

#include "deletesql.h"
#include "findbykeysql.h"
#include "insertsql.h"

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

TagAndQuestionRelationSql::TagAndQuestionRelationSql(Tag *tag,
                                                     Question *question,
                                                     QObject *parent)
    : QObject{parent} {
  this->_tag = tag;
  this->_question = question;
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

template <typename T> void TagAndQuestionRelationSql::executeQuery(T *sql) {
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + COLUMN_TAG_ID, this->_tag->getId());
  query.bindValue(":" + COLUMN_QUESTION_ID, this->_question->getId());

  if (!query.exec()) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isDeleteSql -- the query failed.");
  }
}
