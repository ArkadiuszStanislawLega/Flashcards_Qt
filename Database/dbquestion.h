#ifndef DBQUESTION_H
#define DBQUESTION_H

#include "../Models/question.h"
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
};

#endif // DBQUESTION_H
