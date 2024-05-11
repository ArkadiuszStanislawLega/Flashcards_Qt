#pragma once
#ifndef QUESTION
#define QUESTION
#include <QList>
#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>

#include "../Constants/strings.h"
#include "../Database/crud.h"
#include "../Database/manytomany.h"
#include "tag.h"

class Tag;

class Question : public QObject, public ManyToMany<Tag> {
private:
  Q_OBJECT
  int _id;
  QString _value, _answer;
  QList<Tag *> _tags;
  bool _isActive;
  ///
  /// Check is question and tag can be
  /// related. Id should be setted before called this function. \param t Tag
  /// what we want to make relation with question. \return True if rolation can
  /// be created. Throwing invalid_argument if pointer to tag is empty.
  ///
  bool is_relation_valid(Tag *t);

public:
  Question(QObject *parent = nullptr);
  Question(int, QObject *parent = nullptr);
  Question(int, QString, QString, bool, QList<Tag *>,
           QObject *parent = nullptr);
  ~Question();

  int getId();
  QString getValue() const;
  QString getAnswer() const;
  QList<Tag *> getTags() const;
  bool is_tag_already_related(Tag *);
  bool getIsActive() const;

  void setId(int);
  void setValue(QString);
  void setAnswer(QString);
  void set_tags(QList<Tag *>);
  void setIsActive(bool);

  QString to_string();
  bool isUpdate();
  int findId();
  static Question *convertFromQSqlQuery(QSqlQuery *);
  static QList<Question *> getAll();

  bool isRelationCreated(Tag *);
  bool isRemovedRelation(Tag *);
  bool isAllRelationRemoved();
  QList<Tag *> getAllRelated();
};
#endif
