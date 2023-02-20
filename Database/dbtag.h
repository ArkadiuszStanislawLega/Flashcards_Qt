#ifndef DBTAG_H
#define DBTAG_H

#include "../Models/tag.h"
#include "../Constants/strings.h"
#include <vector>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QString>

class DbTag
{
public:
    DbTag();
    static vector<Tag *> getAllTags();
    static bool isCreate(Tag *);
    static int findId(QString);
    static Tag *read(int);
    static bool isUpdate(Tag *);
    static bool isRemoved(int);
    static int finId(QString);
    static bool isRelationCreated(Tag *, Question *);
    static bool isRelationRemoved(Tag *, Question *);
    static bool isRelationWithTagRemoved(Tag *);

};

#endif // DBTAG_H
