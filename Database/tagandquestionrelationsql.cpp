#include "tagandquestionrelationsql.h"

#include "insertsql.h"

TagAndQuestionRelationSql::TagAndQuestionRelationSql(Tag *tag,
                                                     Question *question,
                                                     QObject *parent)
    : QObject{parent} {
  this->_tag = tag;
  this->_question = question;
}

bool TagAndQuestionRelationSql::isInsertedSql() {
  if (!this->_tag) {
    throw std::invalid_argument("TagAndQuestionRelationSql::isInsertedSql -- "
                                "poninter to tag is empty.");
  }
  if (!this->_question) {
    throw std::invalid_argument("TagAndQuestionRelationSql::isInsertedSql -- "
                                "pointer to question is empty.");
  }

  if (this->_tag->getId() <= 0) {
    throw std::invalid_argument("TagAndQuestionRelationSql::isInsertedSql -- "
                                "property id in tag is zero or subzero.");
  }

  if (this->_question->getId() <= 0) {
    throw std::invalid_argument(
        "TagAndQuestionRelationSql::isInsertedSql -- property id in "
        "question is zero or subzero.");
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

  return true;
}

bool TagAndQuestionRelationSql::isDeleted() {}

bool TagAndQuestionRelationSql::isReaded() {}
