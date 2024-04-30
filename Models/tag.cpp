#include "tag.h"

Tag::Tag(QObject *parent) : QObject(parent) {
  this->_id = 0;
  this->_tag = "";
}

Tag::Tag(int id, QString tag, QObject *parent) : QObject(parent) {
  this->_id = id;
  this->_tag = tag;
}

int Tag::get_id() { return this->_id; }
QString Tag::get_tag() { return this->_tag; }
void Tag::set_id(int id) { this->_id = id; }
void Tag::set_tag(QString tag) { this->_tag = tag; }

bool Tag::is_question_already_related(Question *q) {
  if (!q) {
    throw std::invalid_argument(
        "Tag::is_question_already_related -- Questin is empy");
  }

  for (Tag *t : q->get_tags()) {
    if (t->get_id() == this->_id) {
      return true;
    }
  }
  return false;
}

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

bool Tag::isRelationCreated(Question *q) {
  if (!q) {
    throw std::invalid_argument("Tag::isRlationCreated -- Questin is empy");
  }

  if (this->_id <= 0) {
    return false;
  }

  QSqlQuery query;
  query.prepare(INSERT + TABLE_QUESTIONS_TAGS + "(" + COLUMN_QUESTION_ID +
                ", " + COLUMN_TAG_ID + ")" + VALUES +
                "(:" + COLUMN_QUESTION_ID + ", :" + COLUMN_TAG_ID + ")");
  query.bindValue(":" + COLUMN_QUESTION_ID, q->get_id());
  query.bindValue(":" + COLUMN_TAG_ID, this->_id);

  return isQueryExecuted(&query);
}

bool Tag::isRemovedRelation(Question *q) {
  if (!q) {
    throw std::invalid_argument("Tag::isRemovedRelation -- Questin is empy");
  }

  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::isRemovedRealation -- property id is 0");
  }

  QSqlQuery query;

  query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " + WHERE +
                TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID +
                "=:" + COLUMN_QUESTION_ID + " " + AND + TABLE_QUESTIONS_TAGS +
                "." + COLUMN_TAG_ID + "=:" + COLUMN_TAG_ID);
  query.bindValue(":" + COLUMN_QUESTION_ID, q->get_id());
  query.bindValue(":" + COLUMN_TAG_ID, this->_id);

  return isQueryExecuted(&query);
}

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

  if (!isQueryExecuted(&query)) {
    return {};
  }

  return createQuestionListFromQuery(&query);
}

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

  if (!isQueryExecuted(&query)) {
    return {};
  }

  return createQuestionListFromQuery(&query);
}

QList<Question *> Tag::createQuestionListFromQuery(QSqlQuery *query) {
  QList<Question *> questions{};

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

bool Tag::isAllRelationRemoved() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::getAllRelationRemoved - id <= 0");
  }

  QSqlQuery query;
  query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " + WHERE + COLUMN_TAG_ID +
                "=:" + COLUMN_TAG_ID);
  query.bindValue(":" + COLUMN_TAG_ID, this->_id);

  return isQueryExecuted(&query);
}

bool Tag::isCreate() {
  if (this->_tag == "") {
    throw std::invalid_argument("Tag::isCreate -- tag property is empty");
  }

  QSqlQuery query;

  query.prepare(INSERT + TABLE_TAGS + "(" + COLUMN_TAG + ")" + VALUES +
                "(:" + COLUMN_TAG + ")");

  query.bindValue(":" + COLUMN_TAG, this->_tag);

  return isQueryExecuted(&query);
}

Tag *Tag::isRead() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::isRead -- tag property id is 0");
  }

  QSqlQuery query;

  query.prepare(SELECT + "* " + FROM + TABLE_TAGS + " " + WHERE + COLUMN_ID +
                "=(:" + COLUMN_ID + ") limit 1");
  query.bindValue(":" + COLUMN_ID, this->_id);

  if (!isQueryExecuted(&query)) {
    return this;
  }

  if (!query.next()) {
    return this;
  }

  int idColumn, tagColumn;

  idColumn = query.record().indexOf(COLUMN_ID);
  tagColumn = query.record().indexOf(COLUMN_TAG);

  this->_id = query.value(idColumn).toInt();
  this->_tag = query.value(tagColumn).toString();

  return this;
}

bool Tag::isUpdate() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::isRead -- tag property id is 0");
  }

  QSqlQuery query;
  query.prepare(UPDATE + TABLE_TAGS + " " + SET + COLUMN_TAG +
                "=:" + COLUMN_TAG + " " + WHERE + COLUMN_ID + "=:" + COLUMN_ID);

  query.bindValue(":" + COLUMN_TAG, this->_tag);
  query.bindValue(":" + COLUMN_ID, this->_id);

  return isQueryExecuted(&query);
}

bool Tag::isRemoved() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Tag::isRemoved -- tag property id is 0");
  }

  QSqlQuery query;
  query.prepare(DELETE + TABLE_TAGS + " " + WHERE + COLUMN_ID +
                "=:" + COLUMN_ID);

  query.bindValue(":" + COLUMN_ID, this->_id);

  return isQueryExecuted(&query);
}

int Tag::findId() {
  if (this->_tag == "") {
    throw std::invalid_argument("Tag::findId -- tag property is empty.");
  }

  QSqlQuery query;
  query.prepare(SELECT + "* " + FROM + TABLE_TAGS + " " + WHERE + COLUMN_TAG +
                "=:" + COLUMN_TAG);
  query.bindValue(":" + COLUMN_TAG, this->_tag);

  if (!isQueryExecuted(&query)) {
    throw std::runtime_error("Tag::findId -- query not executed.");
  }

  if (!query.next()) {
    throw std::runtime_error(
        "Tag::findId -- query does not find any tag in database.");
  }

  int idColumn;
  idColumn = query.record().indexOf(COLUMN_ID);

  return query.value(idColumn).toInt();
}

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
