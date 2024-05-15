#include "tag.h"

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
/// \brief Tag::convertFromQSqlQuery Convert QSqlQuery to instance of tag.
/// \param query Query to database with selected tag.
/// \return Instance of tag with properties from databese. Can throw invalid
/// argument.
///
Tag *Tag::convertFromQSqlQuery(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument(
        "Tag::is_question_already_related -- Questin is empy");
  }

  int idColumn, tagColumn;

  idColumn = query->record().indexOf(COLUMN_ID);
  tagColumn = query->record().indexOf(COLUMN_TAG);

  return new Tag(query->value(idColumn).toInt(),
                 query->value(tagColumn).toString());
}

///
/// \brief Tag::isRelationCreated Create relation between tag and question in
/// database. Id should be settled before called. \param q Question with whom
/// relation can be created. \return True if relation successfuly created in
/// databese. Can throw invalid argument if:
/// - question is nullptr,
/// - question id is zero or subzero;
/// - tag is zero or subzero.
///
bool Tag::isRelationCreated(Question *q) {
  if (!q) {
    throw std::invalid_argument("Tag::isRlationCreated -- Question is empy");
  }

  if (q->getId() <= 0) {
    throw std::invalid_argument(
        "Tag::isRelationCreated -- Question->getId is 0");
  }

  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::isRelationCreated -- property id is 0.");
  }

  QSqlQuery query;
  query.prepare(INSERT + TABLE_QUESTIONS_TAGS + "(" + COLUMN_QUESTION_ID +
                ", " + COLUMN_TAG_ID + ")" + VALUES +
                "(:" + COLUMN_QUESTION_ID + ", :" + COLUMN_TAG_ID + ")");
  query.bindValue(":" + COLUMN_QUESTION_ID, q->getId());
  query.bindValue(":" + COLUMN_TAG_ID, this->_id);

  try {
    return isQueryExecuted(&query);
  } catch (std::invalid_argument &e) {
    qWarning() << "Tag::isRelationCreated" << e.what();
    return false;
  }
}

///
/// \brief Tag::isRemovedRelation Removind relation between question and tag in
/// database. Id should be settled before called. \param q Quesiton with whom
/// relation should be removed. \return True if relation removing from databose
/// was successfuly finished. Can throw invalid arguments if:
/// - question is nullptr,
/// - queistoin->id is zero or subzero,
/// - tag->id is zero or subzero.
///
bool Tag::isRemovedRelation(Question *q) {
  if (!q) {
    throw std::invalid_argument("Tag::isRemovedRelation -- Questin is empy");
  }
  if (q->getId() <= 0) {
    throw std::invalid_argument(
        "Tag::isRemovedRelation -- Question->getId is 0.");
  }

  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::isRemovedRealation -- property id is 0");
  }

  QSqlQuery query;

  query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " + WHERE +
                TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID +
                "=:" + COLUMN_QUESTION_ID + " " + AND + TABLE_QUESTIONS_TAGS +
                "." + COLUMN_TAG_ID + "=:" + COLUMN_TAG_ID);
  query.bindValue(":" + COLUMN_QUESTION_ID, q->getId());
  query.bindValue(":" + COLUMN_TAG_ID, this->_id);

  try {
    return isQueryExecuted(&query);
  } catch (std::invalid_argument &e) {
    qWarning() << "Tag::isRemovedRelation " << e.what();
    return false;
  }
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

QList<Question *> Tag::getAllRelated() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::getAllRelated - id <= 0");
  }

  QSqlQuery query;
  query.prepare(SELECT + TABLE_QUESTIONS + "." + COLUMN_ID + ", " +
                COLUMN_VALUE + ", " + COLUMN_ANSWER + " " + FROM +
                TABLE_QUESTIONS + " " + INNER_JOIN + TABLE_QUESTIONS_TAGS +
                " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID +
                "=" + TABLE_QUESTIONS + "." + COLUMN_ID + " " + INNER_JOIN +
                TABLE_TAGS + " " + ON + TABLE_TAGS + "." + COLUMN_ID + "=" +
                TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + " " + WHERE +
                TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=:" + COLUMN_ID +
                " " + ORDER_BY + TABLE_QUESTIONS + "." + COLUMN_VALUE);

  query.bindValue(":" + COLUMN_ID, this->_id);

  try {
    isQueryExecuted(&query);
  } catch (std::invalid_argument &e) {
    qWarning() << "Tag::getAllRelated " << e.what();
    return {};
  }

  return createQuestionListFromQuery(&query);
}

///
/// \brief Tag::getAllActiveRelated Creatind list of active questions related
/// with tag. \return List of active question relatied with tag. Can throw
/// invalid argument if property id is zer or below zero.
///
QList<Question *> Tag::getAllActiveRelated() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::getAllActiveRelated - id <= 0");
  }

  QSqlQuery query;
  query.prepare(
      SELECT + TABLE_QUESTIONS + "." + COLUMN_ID + ", " + TABLE_QUESTIONS +
      "." + COLUMN_VALUE + ", " + TABLE_QUESTIONS + "." + COLUMN_ANSWER + ", " +
      TABLE_QUESTIONS + "." + COLUMN_IS_ACTIVE + " " + FROM + TABLE_QUESTIONS +
      " " + INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON +
      TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=" + TABLE_QUESTIONS +
      "." + COLUMN_ID + " " + INNER_JOIN + TABLE_TAGS + " " + ON + TABLE_TAGS +
      "." + COLUMN_ID + "=" + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + " " +
      WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=:" + COLUMN_ID +
      " AND " + TABLE_QUESTIONS + "." + COLUMN_IS_ACTIVE + "=1 " + ORDER_BY +
      TABLE_QUESTIONS + "." + COLUMN_VALUE);

  query.bindValue(":" + COLUMN_ID, this->_id);

  try {
    isQueryExecuted(&query);
  } catch (std::invalid_argument &e) {
    qWarning() << "Tag::getAllActiveRelated" << e.what();
    return {};
  }

  return createQuestionListFromQuery(&query);
}

///
/// \brief Tag::createQuestionListFromQuery Create list with questions from
/// selected query. \param query Query with data from database. \return List
/// with instances of Questions classes filled with data from database. Can
/// throw invalid argument if query is nullptr.
///
QList<Question *> Tag::createQuestionListFromQuery(QSqlQuery *query) {
  QList<Question *> questions{};

  if (!query) {
    throw std::invalid_argument(
        "Tag::createQuestionListFromQuery -- query is nullptr.");
  }

  try {
    while (query->next()) {
      questions.push_back(Question::convertFromQSqlQuery(query));
    }
  } catch (std::invalid_argument &e) {
    qWarning() << "Question::createQuestionListFromQuery " << e.what();
    return {};
  }

  return questions;
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

///
/// \brief Tag::getAll get all tags from database and throw as list of instances
/// Tag class. \return List of Tags from database.
///
QList<Tag *> Tag::getAll() {
  QList<Tag *> tags;
  QSqlQuery query;

  query.prepare(SELECT + "* " + FROM + TABLE_TAGS + " " + ORDER_BY +
                TABLE_TAGS + "." + COLUMN_TAG);

  if (!query.exec()) {
    throw std::runtime_error("Tag::getAll -- query not executed.");
  }

  while (query.next()) {
    tags.push_back(Tag::convertFromQSqlQuery(&query));
  }
  return tags;
}
