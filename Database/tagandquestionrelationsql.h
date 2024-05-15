#ifndef TAGANDQUESTIONRELATIONSQL_H
#define TAGANDQUESTIONRELATIONSQL_H

#include <QObject>

#include <Constants/strings.h>
#include <Models/question.h>
#include <Models/tag.h>

class TagAndQuestionRelationSql : public QObject {
private:
  Q_OBJECT
  Tag *_tag;
  Question *_question;

public:
  explicit TagAndQuestionRelationSql(Tag *, Question *,
                                     QObject *parent = nullptr);
  bool isInsertedSql();
  bool isDeleted();
  bool isReaded();

signals:
};

#endif // TAGANDQUESTIONRELATIONSQL_H
