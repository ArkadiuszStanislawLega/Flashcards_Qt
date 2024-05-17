#include "question.h"

#include <Database/insertsql.h>
#include <Database/questionmodelsql.h>
#include <Database/selectsql.h>
#include <Database/wheresql.h>

Question::~Question() { qDebug() << "Destruction: " << this; }

Question::Question(QObject *parent) : QObject(parent) {
  this->_id = 0;
  this->_value = "";
  this->_answer = "";
}

Question::Question(int id, QObject *parent) : Question(parent) {
  this->_id = id;
}

Question::Question(int id, QString value, QString answer, bool isActive,
                   QList<Tag *> tags, QObject *parent)
    : Question(id, parent) {
  this->_value = value;
  this->_answer = answer;
  this->_tags = tags;
  this->_isActive = isActive;
}

void Question::setId(int value) { this->_id = value; }
QList<Tag *> Question::getTags() const { return this->_tags; }
QString Question::getValue() const { return this->_value; }
QString Question::getAnswer() const { return this->_answer; }
int Question::getId() { return this->_id; }
bool Question::getIsActive() const { return this->_isActive; }
void Question::setAnswer(QString value) { this->_answer = value; }
void Question::setValue(QString value) { this->_value = value; }
void Question::setIsActive(bool value) { _isActive = value; }

bool Question::is_tag_already_related(Tag *t) {
  if (!t) {
    throw std::invalid_argument(
        "Question::is_tag_already_related - tag is empty.");
  }

  for (Tag *tag : this->_tags) {
    if (tag->getId() == t->getId()) {
      return true;
    }
  }

  return false;
}

QString Question::to_string() {
  return QString::number(this->_id) + ". " + this->_value + " " + this->_answer;
}

/*! Check is question and tag can be related. Id should be setted before called
   this function.
   \param Tag t Tag what we want to make relation with question.
   \return True if rolation can be created. Throwing invalid_argument if pointer
   to tag is empty.
*/
bool Question::is_relation_valid(Tag *t) {
  if (t == nullptr) {
    throw std::invalid_argument("Question::is_relation_valid - tag is empty");
  }

  if (t->getId() <= 0)
    return false;
  if (this->_id <= 0)
    return false;
  if (this->is_tag_already_related(t))
    return false;

  return true;
}

///
/// \brief Question::isRelationCreated creating new relation with tag in
/// database. \param t Tag what we want create relation. \return true if
/// relation has been created. Throw invalid argument if pointer to tag is empty
/// and if query failed.
///
bool Question::isRelationCreated(Tag *t) {
  if (!t) {
    throw std::invalid_argument("Question::is_relation_valid - tag is empty");
  }
  try {
    if (!this->is_relation_valid(t)) {
      return false;
    }
  } catch (std::invalid_argument &e) {
    qWarning() << e.what();
    return false;
  }

  QSqlQuery query;
  query.prepare(INSERT + TABLE_QUESTIONS_TAGS + "(" + COLUMN_QUESTION_ID +
                ", " + COLUMN_TAG_ID + ")" + VALUES +
                "(:" + COLUMN_QUESTION_ID + ", :" + COLUMN_TAG_ID + ")");
  query.bindValue(":" + COLUMN_QUESTION_ID, this->_id);
  query.bindValue(":" + COLUMN_TAG_ID, t->getId());
  if (!query.exec()) {
    throw std::invalid_argument(
        "Question::isRelationCreated - the query failed.");
  }
  return true;
}

///
/// \brief Question::isRemovedRelation Romoving related tag with question in
/// databese. Id should be setted befored called. \param t Tag which rolation
/// should be removed. \return true if relation has been successful removed.
/// Throwing invalid_argument if tag is empty or query failed.
///
bool Question::isRemovedRelation(Tag *t) {
  if (!t) {
    throw std::invalid_argument("Question::isRemovedRelation - tag is empy.");
  }

  try {
    if (!this->is_relation_valid(t)) {
      return false;
    }

  } catch (std::invalid_argument &e) {
    qWarning() << e.what();
    return false;
  }

  QSqlQuery query;
  query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " + WHERE +
                TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID +
                "=:" + COLUMN_QUESTION_ID + " " + AND + TABLE_QUESTIONS_TAGS +
                "." + COLUMN_TAG_ID + "=:" + COLUMN_TAG_ID);
  query.bindValue(":" + COLUMN_QUESTION_ID, this->_id);
  query.bindValue(":" + COLUMN_TAG_ID, t->getId());

  if (!query.exec()) {
    throw std::invalid_argument(
        "Question::isRemovedRelation - the query failed.");
  }
  return true;
}

///
/// \brief Question::getAllRelated get all tags related with question. Before
/// use set id. \return list with tags if relation exists. Could be possible to
/// throw invalid_argument:
/// - id = 0,
/// - query failed,
/// - converting query to Tag object fail.
///
QList<Tag *> Question::getAllRelated() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Question::getAllRelated - _id <= 0");
  }

  QSqlQuery query;
  this->_tags.clear();

  query.prepare(SELECT + TABLE_TAGS + "." + COLUMN_ID + ", " + COLUMN_TAG +
                " " + FROM + TABLE_TAGS + " " + INNER_JOIN +
                TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." +
                COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " +
                INNER_JOIN + TABLE_QUESTIONS + " " + ON + TABLE_QUESTIONS +
                "." + COLUMN_ID + "=" + TABLE_QUESTIONS_TAGS + "." +
                COLUMN_QUESTION_ID + " " + WHERE + TABLE_QUESTIONS_TAGS + "." +
                COLUMN_QUESTION_ID + "=:" + COLUMN_QUESTION_ID);

  query.bindValue(":" + COLUMN_QUESTION_ID, this->_id);

  if (!query.exec()) {
    throw std::invalid_argument("Question::getAllRelated - the query failed.");
  }

  try {

    while (query.next()) {
      this->_tags.append(Tag::convertFromQSqlQuery(&query));
    }

  } catch (std::invalid_argument &e) {
    qWarning() << "Question:: getAllRelated" << e.what();
    return {};
  }

  return this->_tags;
}
///
/// \brief Question::getAll create list of all Questions from the database.
/// \return List with all questions in database. Could be possible to throw
/// invalid_argument when executing query failed or convertion query to objects
/// failed.
///
QList<Question *> Question::getAll() {
  QList<Question *> questions;
  QSqlQuery query;

  query.prepare(SELECT + "* " + FROM + TABLE_QUESTIONS + " " + ORDER_BY +
                TABLE_QUESTIONS + "." + VALUES);

  if (!query.exec()) {
    throw std::invalid_argument("Question::getAll - the query failed.");
  }

  try {

    while (query.next()) {
      questions.append(Question::convertFromQSqlQuery(&query));
    }

  } catch (std::invalid_argument &e) {
    qWarning() << "Question::getAll()" << e.what();
    return {};
  }
  return questions;
}
///
/// \brief Question::convertFromQSqlQuery convert QsqlQuery to Instance of
/// Question class. \param query QsqlQuery select from database. \return
/// Instance of class Queostion with arg selecteg from database.
///
Question *Question::convertFromQSqlQuery(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument("Pointer to query is empty.");
  }

  Question *q = new Question();
  int columnId, columnValue, columnAnswer, columnIsActive;

  columnId = query->record().indexOf(COLUMN_ID);
  columnIsActive = query->record().indexOf(COLUMN_IS_ACTIVE);
  columnValue = query->record().indexOf(COLUMN_VALUE);
  columnAnswer = query->record().indexOf(COLUMN_ANSWER);

  q->setId(query->value(columnId).toInt());
  q->setIsActive(query->value(columnIsActive).toBool());
  q->setAnswer(query->value(columnAnswer).toString());
  q->setValue(query->value(columnValue).toString());
  return q;
}
///
/// \brief Question::isAllRelationRemoved Remove all related tags with question.
/// Throwing invalid_argument if id = 0 \return true if all relations from
/// database are removed.
///
bool Question::isAllRelationRemoved() {
  if (this->_id <= 0) {
    throw std::invalid_argument("Question::isAllRelationRemoved - _id = 0");
  }

  QSqlQuery query;
  query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " + WHERE +
                COLUMN_QUESTION_ID + "=:" + COLUMN_QUESTION_ID);
  query.bindValue(":" + COLUMN_QUESTION_ID, this->_id);

  if (!query.exec()) {
    throw std::invalid_argument(
        "Question::isAllRlationRemoved - the query failed.");
  }
  return true;
}

void Question::setTags(QList<Tag *> t) { this->_tags = t; }
