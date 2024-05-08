#include "question.h"

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
QList<Tag *> Question::get_tags() const { return this->_tags; }
QString Question::get_value() const { return this->_value; }
QString Question::get_answer() const { return this->_answer; }
int Question::get_id() { return this->_id; }
void Question::setAnswer(QString value) { this->_answer = value; }
void Question::setValue(QString value) { this->_value = value; }
bool Question::get_isActive() const { return this->_isActive; }
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

///
/// \brief Question::isCreate creating query in database.
/// \return created question, if fail to execute throwing invalid_argument.
///
bool Question::isCreate() {
  QSqlQuery query;

  query.prepare(INSERT + TABLE_QUESTIONS + "(" + COLUMN_VALUE + ", " +
                COLUMN_ANSWER + ", " + COLUMN_IS_ACTIVE + ")" + VALUES +
                "(:" + COLUMN_VALUE + ", :" + COLUMN_ANSWER +
                ", :" + COLUMN_IS_ACTIVE + ")");

  query.bindValue(":" + COLUMN_VALUE, this->_value);
  query.bindValue(":" + COLUMN_ANSWER, this->_answer);
  query.bindValue(":" + COLUMN_IS_ACTIVE, this->_isActive);

  if (!query.exec()) {
    throw std::invalid_argument("Question::isCreate - the query fialed");
  }

  return true;
}

///
/// \brief Question::isRead is reading Queistion from database.
/// \return Quetion from database if id is setted else throw invalid_argument.
Question *Question::isRead() {

  QuestionModelSql *sql = new QuestionModelSql(this, this);
  return sql->selectQuestion(this->_id);
}

///
/// \brief Question::isUpdate Updating question in database.
/// \return True if updated successfull, throw invalid_argument if execution not
/// possible.
///
bool Question::isUpdate() {
  QSqlQuery query;
  query.prepare(UPDATE + TABLE_QUESTIONS + " " + SET + COLUMN_VALUE + "=:" +
                COLUMN_VALUE + ", " + COLUMN_ANSWER + "=:" + COLUMN_ANSWER +
                ", " + COLUMN_IS_ACTIVE + "=:" + COLUMN_IS_ACTIVE + " " +
                WHERE + COLUMN_ID + "=:" + COLUMN_ID);
  query.bindValue(":" + COLUMN_VALUE, this->_value);
  query.bindValue(":" + COLUMN_ANSWER, this->_answer);
  query.bindValue(":" + COLUMN_IS_ACTIVE, this->_isActive);
  query.bindValue(":" + COLUMN_ID, this->_id);
  if (!query.exec()) {
    throw std::invalid_argument("Question::isUpdate - the query failed.");
  }
  return true;
}

///
/// \brief Question::isRemoved removing question from databese. Should be setted
/// id before colled. \return True if successful removed question from database.
/// Throw invalid argumen if id = 0, or query filed.
///
bool Question::isRemoved() {
  if (this->_id) {
    throw std::invalid_argument("Queistion::isRemoved - _id = 0");
  }

  QSqlQuery query;
  query.prepare(DELETE + TABLE_QUESTIONS + " " + WHERE + COLUMN_ID +
                "=:" + COLUMN_ID);
  query.bindValue(":" + COLUMN_ID, this->_id);
  if (!query.exec()) {
    throw std::invalid_argument("Question::isRemoved - the query failed.");
  }

  return true;
}

///
/// \brief Question::findId searching database for question with value and
/// answer as setted in properties. \return id of question with the same values
/// as property. Throwing invalid argument if query failed or if can't find
/// question.
///
int Question::findId() {
  QSqlQuery query;
  query.prepare(SELECT + "* " + FROM + TABLE_QUESTIONS + " " + WHERE +
                COLUMN_VALUE + "=:" + COLUMN_VALUE + " " + AND + COLUMN_ANSWER +
                "=:" + COLUMN_ANSWER + " limit 1");
  query.bindValue(":" + COLUMN_VALUE, this->_value);
  query.bindValue(":" + COLUMN_ANSWER, this->_answer);

  if (!query.exec()) {
    throw std::invalid_argument("Question::findId - the query failed.");
  }

  if (!query.next()) {
    throw std::invalid_argument(
        "Question::findId - can't find question in database.");
  }

  int idColumn;

  idColumn = query.record().indexOf(COLUMN_ID);
  this->_id = query.value(idColumn).toInt();

  return this->_id;
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

void Question::set_tags(QList<Tag *> t) { this->_tags = t; }
