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

void Question::setTags(QList<Tag *> t) { this->_tags = t; }
