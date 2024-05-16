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

class Tag : public QObject, public ManyToMany<Question> {
private:
  Q_OBJECT
  int _id;
  QString _tag;

  bool isQueryExecuted(QSqlQuery *query);

  QList<Question *> createQuestionListFromQuery(QSqlQuery *query);

public:
  Tag(QObject *parent = nullptr);
  Tag(QString, QObject *parent = nullptr);
  Tag(int, QString, QObject *parent = nullptr);

  int getId();
  QString getTag();

  void setId(int);
  void setTag(QString);
  bool isQuestionAlreadyRelated(Question *);
  static Tag *convertFromQSqlQuery(QSqlQuery *);

  // ManyToMany interface
  bool isRelationCreated(Question *);
  bool isRemovedRelation(Question *);
  QList<Question *> getAllRelated();
  QList<Question *> getAllActiveRelated();
  bool isAllRelationRemoved();

  static QList<Tag *> getAll();
};
#endif
