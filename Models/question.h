#pragma once
#ifndef QUESTION
#define QUESTION
#include <QList>
#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>

#include "tag.h"
#include <Constants/strings.h>

class Tag;

class Question : public QObject {
private:
  Q_OBJECT
  int _id;
  QString _value, _answer;
  QList<Tag *> _tags;
  bool _isActive;

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
  bool getIsActive() const;

  void setId(int);
  void setValue(QString);
  void setAnswer(QString);
  void setTags(QList<Tag *>);
  void setIsActive(bool);

  QString to_string();
};
#endif
