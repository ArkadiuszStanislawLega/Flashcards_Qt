#include "dbmanager.h"

DbManager::DbManager(){
    this->_database = QSqlDatabase::addDatabase("QSQLITE");
    this->_database.setDatabaseName("fiszka.db");

    if (!this->_database.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
       qDebug() << "Database: connection ok";
       this->CreateTables();
    }
}

DbManager::DbManager(const QString &path){
    this->_database = QSqlDatabase::addDatabase("QSQLITE");
    this->_database.setDatabaseName(path);

    if (!this->_database.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
       qDebug() << "Database: connection ok";
       this->CreateTables();
    }
}

void DbManager::CreateTables(){
    this->CreateTableQuestions();
    this->CreateTableTags();
    this->CreateTableQuestionsTags();
}

void DbManager::CreateTableQuestions(){
    QSqlQuery query;
    QString create_table_questions = "create table if not exists Questions"
            "(id integer primary key autoincrement not null,"
            "Value Text not null,"
            "Answer Text not null);";
    query.exec(create_table_questions);
}

void DbManager::CreateTableTags(){
    QSqlQuery query;
    QString create_table_tags = "create table if not exists Tags"
            "(id integer primary key autoincrement not null,"
            "tag Text not null);";
    query.exec(create_table_tags);
}

void DbManager::CreateTableQuestionsTags(){
    QSqlQuery query;
    QString w = CREATE_TABLE_IF_NOT_EXISTS + TABLE_QUESTIONS_TAGS + "(" +
                  COLUMN_ID + " " + PRIMARY_KEY + ", " +
                  COLUMN_QUESTION_ID + " " + INTEGER_NOT_NULL + ", " +
                  COLUMN_TAG_ID + " " + INTEGER_NOT_NULL + "," +
                  FOREIGN_KEY + "(" + COLUMN_QUESTION_ID + ")" + REFERENCES + TABLE_QUESTIONS + "(" + COLUMN_ID + ")" +
                  FOREIGN_KEY + "(" + COLUMN_TAG_ID + ")" + REFERENCES + TABLE_TAGS + "(" + COLUMN_ID + "))";
    qDebug() << w;
    query.exec(w);
}
