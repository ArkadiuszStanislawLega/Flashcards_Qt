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
  bool isQuestionAndTagValid();
  template <typename T> void executeQuery(T *);

public:
  explicit TagAndQuestionRelationSql(Tag *, Question *,
                                     QObject *parent = nullptr);
  bool isInsertedSql();
  bool isDeletedSql();
  bool isSelectedSql();
  bool isAlreadyRelated();
  bool isAllRelationRemoved();
  QList<Tag *> getRelatedTags();
  QList<Question *> getRelatedQuestions();
  QList<Question *> getRelatedActiveQuesitons();

signals:
};

#endif // TAGANDQUESTIONRELATIONSQL_H
