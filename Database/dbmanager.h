#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "../Constants/strings.h"
#include <qstring.h>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

class DbManager
{
public:
    DbManager();
    DbManager(const QString &);
    void ReadTag(int id);

private:
    QSqlDatabase _database;
    void CreateTables();
    void CreateTableQuestions();
    void CreateTableTags();
    void CreateTableQuestionsTags();
};

#endif // DBMANAGER_H
