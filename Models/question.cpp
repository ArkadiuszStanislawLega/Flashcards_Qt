#include "question.h"

#include <Database/SqlGenerators/insertsql.h>
#include <Database/SqlGenerators/selectsql.h>
#include <Database/SqlGenerators/wheresql.h>
#include <Database/SqlModels/questionmodelsql.h>

Question::~Question() {
  qDebug() << "Destruction: " << this << metaObject()->metaType()
           << metaObject()->className();
}

Question::Question(QObject *parent) : QObject(parent) {
  this->_id = 0;
  this->_value = "";
  this->_answer = "";
  // this->setObjectName("Question");
  metaObject()->className();
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

QString Question::to_string() {
  return QString::number(this->_id) + ". " + this->_value + " " + this->_answer;
}

void Question::setTags(QList<Tag *> t) { this->_tags = t; }
