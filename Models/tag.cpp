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
  for (Tag *t : q->get_tags()) {
    if (t->get_id() == this->_id) {
      return true;
    }
  }
  return false;
}

bool Tag::isRelationCreated(Question *q) {
  if (q == nullptr) {
    return false;
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
  return query.exec();
}

bool Tag::isRemovedRelation(Question *q) {
  if (q == nullptr) {
    return false;
  }

  if (this->_id <= 0) {
    return false;
  }

  QSqlQuery query;
  query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " + WHERE +
                TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID +
                "=:" + COLUMN_QUESTION_ID + " " + AND + TABLE_QUESTIONS_TAGS +
                "." + COLUMN_TAG_ID + "=:" + COLUMN_TAG_ID);
  query.bindValue(":" + COLUMN_QUESTION_ID, q->get_id());
  query.bindValue(":" + COLUMN_TAG_ID, this->_id);
  return query.exec();
}
QList<Question *> Tag::getAllRelated() {
  QList<Question *> questions;
  if (this->_id <= 0) {
    return questions;
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
  if (!query.exec()) {
    return questions;
  }

  while (query.next()) {
    Question *q = new Question();
    int idColumn, valueColumn, answerColumn, isActiveColumn;

    idColumn = query.record().indexOf(COLUMN_ID);
    isActiveColumn = query.record().indexOf(COLUMN_IS_ACTIVE);
    valueColumn = query.record().indexOf(COLUMN_VALUE);
    answerColumn = query.record().indexOf(COLUMN_ANSWER);

    q->set_id(query.value(idColumn).toInt());
    q->set_isActive(query.value(isActiveColumn).toBool());
    q->set_value(query.value(valueColumn).toString());
    q->set_answer(query.value(answerColumn).toString());

    questions.push_back(q);
  }
  return questions;
}
QList<Question *> Tag::getAllActiveRelated() {
  QList<Question *> questions;
  if (this->_id <= 0) {
    return questions;
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

  if (!query.exec()) {
    return questions;
  }

  while (query.next()) {
    Question *q = new Question();
    int idColumn, valueColumn, answerColumn, isActiveColumn;

    idColumn = query.record().indexOf(COLUMN_ID);
    valueColumn = query.record().indexOf(COLUMN_VALUE);
    answerColumn = query.record().indexOf(COLUMN_ANSWER);
    isActiveColumn = query.record().indexOf(COLUMN_IS_ACTIVE);

    q->set_id(query.value(idColumn).toInt());
    q->set_isActive(query.value(isActiveColumn).toBool());
    q->set_value(query.value(valueColumn).toString());
    q->set_answer(query.value(answerColumn).toString());

    questions.push_back(q);
  }
  return questions;
}

bool Tag::isAllRelationRemoved() {

  if (this->_id <= 0) {
    return false;
  }
  QSqlQuery query;
  query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " + WHERE + COLUMN_TAG_ID +
                "=:" + COLUMN_TAG_ID);
  query.bindValue(":" + COLUMN_TAG_ID, this->_id);
  return query.exec();
}

bool Tag::isCreate() {
  if (this->_tag == "") {
    return false;
  }

  QSqlQuery query;

  query.prepare(INSERT + TABLE_TAGS + "(" + COLUMN_TAG + ")" + VALUES +
                "(:" + COLUMN_TAG + ")");

  query.bindValue(":" + COLUMN_TAG, this->_tag);

  return query.exec();
}

Tag *Tag::isRead() {
  if (this->_id <= 0) {
    return this;
  }

  QSqlQuery query;
  query.prepare(SELECT + "* " + FROM + TABLE_TAGS + " " + WHERE + COLUMN_ID +
                "=(:" + COLUMN_ID + ") limit 1");
  query.bindValue(":" + COLUMN_ID, this->_id);

  if (!query.exec()) {
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
    return false;
  }

  QSqlQuery query;
  query.prepare(UPDATE + TABLE_TAGS + " " + SET + COLUMN_TAG +
                "=:" + COLUMN_TAG + " " + WHERE + COLUMN_ID + "=:" + COLUMN_ID);

  query.bindValue(":" + COLUMN_TAG, this->_tag);
  query.bindValue(":" + COLUMN_ID, this->_id);
  return query.exec();
}

bool Tag::isRemoved() {
  if (this->_id <= 0) {
    return false;
  }

  QSqlQuery query;
  query.prepare(DELETE + TABLE_TAGS + " " + WHERE + COLUMN_ID +
                "=:" + COLUMN_ID);

  query.bindValue(":" + COLUMN_ID, this->_id);
  return query.exec();
}

int Tag::findId() {
  if (this->_tag == "") {
    return -1;
  }

  QSqlQuery query;
  query.prepare(SELECT + "* " + FROM + TABLE_TAGS + " " + WHERE + COLUMN_TAG +
                "=:" + COLUMN_TAG);
  query.bindValue(":" + COLUMN_TAG, this->_tag);

  if (!query.exec()) {
    return -1;
  }

  if (!query.next()) {
    return -1;
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
    return tags;
  }

  while (query.next()) {
    Tag *t = new Tag();
    int idColumn, tagColumn;

    idColumn = query.record().indexOf(COLUMN_ID);
    tagColumn = query.record().indexOf(COLUMN_TAG);

    t->set_id(query.value(idColumn).toInt());
    t->set_tag(query.value(tagColumn).toString());

    tags.push_back(t);
  }
  return tags;
}
