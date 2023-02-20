#ifndef DBRELATIONQUESTIONTAG_H
#define DBRELATIONQUESTIONTAG_H

#include "../Models/question.h"
#include "../Models/tag.h"
#include "../Constants/strings.h"

#include <vector>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>

using std::vector;

class DbRelationQuestionTag
{
public:
    DbRelationQuestionTag();
    static bool isRelationCreated(Question *, Tag *);
    static bool isRelationRemoved(Question *, Tag *);
    static bool isAllRelationWithQuestionRemoved(Question *);
    static bool isAllRelationWithTagRemoved(Tag *);
    static vector<Tag *> readRelatedTags(Question *);
    static vector<Question *> readRelatedQuestions(Tag *);
};

#endif // DBRELATIONQUESTIONTAG_H
