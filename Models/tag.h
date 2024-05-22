#pragma once
#ifndef TAG
#define TAG
#include <QList>
#include <QObject>
#include <QString>

#include "question.h"

class Question;

class Tag : public QObject {
private:
  Q_OBJECT
  int _id;
  QString _tag;

public:
  Tag(QObject *parent = nullptr);
  Tag(QString, QObject *parent = nullptr);
  Tag(int, QString, QObject *parent = nullptr);

  int getId();
  const QString getTag();

  void setId(int);
  void setTag(QString);
};
#endif
