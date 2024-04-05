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

class Question : public QObject, public Crud<Question>, public ManyToMany<Tag> {
private:
  Q_OBJECT
  int _id;
  QString _value, _answer;
  QList<Tag *> _tags;
  bool is_relation_valid(Tag *t);

public:
  Question(QObject *parent = nullptr);
  Question(int, QObject *parent = nullptr);
  Question(int, QString, QString, QList<Tag *>, QObject *parent = nullptr);
  ~Question();

  int get_id();
  QString get_value();
  QString get_answer();
  QList<Tag *> get_tags();
  bool is_tag_already_related(Tag *);

  void set_id(int);
  void set_value(QString);
  void set_answer(QString);
  void set_tags(QList<Tag *>);

  QString to_string();
  bool isCreate();
  Question *isRead();
  bool isUpdate();
  bool isRemoved();
  int findId();
  static QList<Question *> getAll();

  bool isRelationCreated(Tag *);
  bool isRemovedRelation(Tag *);
  bool isAllRelationRemoved();
  QList<Tag *> getAllRelated();
};
#endif
