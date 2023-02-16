#include "dbmanager.h"

DbManager::DbManager(){
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->database.setDatabaseName("fiszka.db");

    if (!this->database.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

DbManager::DbManager(const QString &path){
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->database.setDatabaseName(path);

    if (!this->database.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

void DbManager::ReadTag(int id){
    int idValue, idAnswer;
    QSqlQuery query("Select * from Questions");
    idValue = query.record().indexOf("Value");
    idAnswer = query.record().indexOf("Answer");

    while(query.next()){
        QString value, answer;
        value = query.value(idValue).toString();
        answer = query.value(idAnswer).toString();
        qDebug() << value << answer;
    }

    QSqlQuery query1("SELECT * FROM Tags");
           int tag = query1.record().indexOf("Tag");
           int i = 0;
           while (query1.next())
           {
              QString name = query1.value(tag).toString();
              qDebug() << name;
           }
}
