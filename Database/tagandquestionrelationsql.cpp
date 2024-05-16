#include "tagandquestionrelationsql.h"

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
    }
    InsertSql sql =
        InsertSql(TABLE_QUESTIONS_TAGS, {COLUMN_TAG_ID, COLUMN_TAG_ID}, this);

    QSqlQuery query;
    query.prepare(sql.generate());
    query.bindValue(":" + COLUMN_TAG_ID, this->_tag->getId());
    query.bindValue(":" + COLUMN_QUESTION_ID, this->_question->getId());

    if (!query.exec()) {
      throw std::invalid_argument(
          "TagAndQuestionRelationSql::isInsertedSql -- the query failed.");
    }

  } catch (std::invalid_argument &e) {
  }

  return true;
}

bool TagAndQuestionRelationSql::isDeleted() {
  if (!this->_tag) {
    throw std::invalid_argument("TagAndQuestionRelationSql::isDeleted -- "
                                "poninter to tag is empty.");
  }
  if (!this->_question) {
    throw std::invalid_argument("TagAndQuestionRelationSql::isDeleted -- "
                                "pointer to question is empty.");
  }

  if (this->_tag->getId() <= 0) {
    throw std::invalid_argument("TagAndQuestionRelationSql::isDeleted -- "
                                "property id in tag is zero or subzero.");
  }

  if (this->_question->getId() <= 0) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isDeleted -- property id in "
        "question is zero or subzero.");
  }
}

bool TagAndQuestionRelationSql::isReaded() {}
