#ifndef DBQUESTION_H
#define DBQUESTION_H

#include "../Models/question.h"
#include "../Models/tag.h"
#include "../Constants/strings.h"
#include <vector>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QString>

using std::vector;

class DbQuestion
{
public:
    DbQuestion();
    static vector<Question *> getAllQuestions();
    static bool isCreate(Question *);
    static Question *read(int);
    static bool isUpdate(Question *);
    static bool isRemoved(int );
    static int findId(QString, QString);
    static bool isRelationCreated(Question *, Tag *);
    static bool isRelationRemoved(Question *, Tag *);
    static bool isAllRelationWithQuestionRemoved(Question *);
    static bool isRelationWithTagRemoved(Tag *);
    static vector<Tag *> readRelatedTags(Question *);
};

#endif // DBQUESTION_H
