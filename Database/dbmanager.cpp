#include "dbmanager.h"

DbManager::DbManager(){
    this->_database = QSqlDatabase::addDatabase("QSQLITE");
    this->_database.setDatabaseName(DATABASE_NAME);

    if (!this->_database.open())
    {
       qDebug() << ERROR_CONNECTION_WITH_DATABASE;
    }
    else
    {
       qDebug() << CONNECTION_OK;
       this->CreateTables();
    }
}

DbManager::DbManager(const QString &path){
    this->_database = QSqlDatabase::addDatabase("QSQLITE");
    this->_database.setDatabaseName(path);

    if (!this->_database.open())
    {
       qDebug() << ERROR_CONNECTION_WITH_DATABASE;
    }
    else
    {
       qDebug() << CONNECTION_OK;
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
    query.prepare(CREATE_TABLE_IF_NOT_EXISTS + TABLE_QUESTIONS + "(" +
                  COLUMN_ID + " " + PRIMARY_KEY + ", " +
                  COLUMN_VALUE + " " + TEXT + ", " +
                  COLUMN_ANSWER + " " + TEXT + ")");
    query.exec();
}

void DbManager::CreateTableTags(){
    QSqlQuery query;
    query.prepare(CREATE_TABLE_IF_NOT_EXISTS + TABLE_TAGS + "(" +
                  COLUMN_ID + " " + PRIMARY_KEY + ", " +
                  COLUMN_TAG + " " + TEXT + ")");
    query.exec();
}

void DbManager::CreateTableQuestionsTags(){
    QSqlQuery query;
    query.prepare(CREATE_TABLE_IF_NOT_EXISTS + TABLE_QUESTIONS_TAGS + "(" +
                  COLUMN_ID + " " + PRIMARY_KEY + ", " +
                  COLUMN_QUESTION_ID + " " + INTEGER_NOT_NULL + ", " +
                  COLUMN_TAG_ID + " " + INTEGER_NOT_NULL + "," +
                  FOREIGN_KEY + "(" + COLUMN_QUESTION_ID + ")" + REFERENCES + TABLE_QUESTIONS + "(" + COLUMN_ID + ")" +
                  FOREIGN_KEY + "(" + COLUMN_TAG_ID + ")" + REFERENCES + TABLE_TAGS + "(" + COLUMN_ID + "))");
    query.exec();
}
