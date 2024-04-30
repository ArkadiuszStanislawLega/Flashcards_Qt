#pragma once
#ifndef TAG
#define TAG
#include <QList>
#include <QObject>
#include <QString>

#include "../Constants/strings.h"
#include "../Database/crud.h"
#include "../Database/manytomany.h"
#include "question.h"

class Question;

class Tag : public QObject, public Crud<Tag>, public ManyToMany<Question> {
private:
  Q_OBJECT
  int _id;
  QString _tag;

  isQueryExecute(QSqlQuery *query);

public:
  Tag(QObject *parent = nullptr);
  Tag(int, QString, QObject *parent = nullptr);

  int get_id();
  QString get_tag();

  void set_id(int);
  void set_tag(QString);
  bool is_question_already_related(Question *);
  static Tag *convertFromQSqlQuery(QSqlQuery *);

  // ManyToMany interface
  bool isRelationCreated(Question *);
  bool isRemovedRelation(Question *);
  QList<Question *> getAllRelated();
  QList<Question *> getAllActiveRelated();
  bool isAllRelationRemoved();

  // Db_crud interface
  bool isCreate();
  Tag *isRead();
  bool isUpdate();
  bool isRemoved();
  int findId();
  static QList<Tag *> getAll();
};
#endif
