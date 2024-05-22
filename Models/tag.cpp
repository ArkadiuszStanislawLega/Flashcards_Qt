#include "tag.h"

#include <Converters/fromquerytoquestionconverter.h>

Tag::Tag(QObject *parent) : QObject(parent) {
  this->_id = 0;
  this->_tag = {};
}

Tag::Tag(QString tag, QObject *parent) : Tag(parent) { this->_tag = tag; }

Tag::Tag(int id, QString tag, QObject *parent) : QObject(parent) {
  this->_id = id;
  this->_tag = tag;
}

int Tag::getId() { return this->_id; }
const QString Tag::getTag() { return this->_tag; }
void Tag::setId(int id) { this->_id = id; }
void Tag::setTag(QString tag) { this->_tag = tag; }
