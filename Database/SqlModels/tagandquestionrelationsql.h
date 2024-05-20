#ifndef TAGANDQUESTIONRELATIONSQL_H
#define TAGANDQUESTIONRELATIONSQL_H

#include <QObject>

#include <Constants/strings.h>
#include <Models/question.h>
#include <Models/tag.h>

#include <Database/SqlGenerators/deletesql.h>
#include <Database/SqlGenerators/findbykeysql.h>
#include <Database/SqlGenerators/insertsql.h>
#include <Database/SqlGenerators/selectsql.h>
#include <Database/SqlGenerators/selectwithcriteriasql.h>
#include <Database/SqlGenerators/selectwithjoinsql.h>
#include <Database/SqlGenerators/updatesql.h>

#include <Converters/fromquerytoquestionconverter.h>
#include <Converters/fromquerytotagconverter.h>
#include <Converters/fromquerytovalueconverter.h>

#include <QException>

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
