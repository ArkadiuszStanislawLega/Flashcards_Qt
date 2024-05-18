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
