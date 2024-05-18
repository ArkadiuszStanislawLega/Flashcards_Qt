#include "tag.h"

#include <Converters/fromquerytoquestionconverter.h>

Tag::Tag(QObject *parent) : QObject(parent) {
  this->_id = 0;
  this->_tag = "";
}

Tag::Tag(QString tag, QObject *parent) : Tag(parent) { this->_tag = tag; }

Tag::Tag(int id, QString tag, QObject *parent) : QObject(parent) {
  this->_id = id;
  this->_tag = tag;
}

int Tag::getId() { return this->_id; }
QString Tag::getTag() { return this->_tag; }
void Tag::setId(int id) { this->_id = id; }
void Tag::setTag(QString tag) { this->_tag = tag; }

///
/// \brief Tag::isQuestionAlreadyRelated Check in database that tag is related
/// with quesiton. \param q Question with whom can be related. \return true if
/// question is relatied with tag. Can throw invalid argument.
///
bool Tag::isQuestionAlreadyRelated(Question *q) {
  if (!q) {
    throw std::invalid_argument(
        "Tag::isQuestionAlreadyRelated -- Question is empy");
  }

  for (Tag *t : q->getTags()) {
    if (t->getId() == this->_id) {
      return true;
    }
  }
  return false;
}

///
/// \brief Tag::isQueryExecuted Executing query, if can't execute throw
/// invalid_argument. \param query Query to execute. \return True if query was
/// successfuly executed.
///
bool Tag::isQueryExecuted(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument("Tag::isQueryExecuted -- Query is empy.");
  }

  if (!query->exec()) {
    throw std::invalid_argument("Tag::isQueryExecuted -- the query failed.");
  }

  return true;
}

///
/// \brief Tag::isAllRelationRemoved Removind all relation between tag and
/// queistions. Id should be settled before called. \return True if all relation
/// was successfuly removed from database. Can throw invalid argumnet if id is
/// zero or subzero.
///
bool Tag::isAllRelationRemoved() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::getAllRelationRemoved - id <= 0");
  }

  QSqlQuery query;
  query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " + WHERE + COLUMN_TAG_ID +
                "=:" + COLUMN_TAG_ID);
  query.bindValue(":" + COLUMN_TAG_ID, this->_id);

  try {
    return isQueryExecuted(&query);
  } catch (std::invalid_argument &e) {
    qWarning() << "Tag::isAllRelationRemoved" << e.what();
    return false;
  }
}
