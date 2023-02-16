#ifndef DBMANAGER_H
#define DBMANAGER_H

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
    QSqlDatabase database;
};

#endif // DBMANAGER_H
