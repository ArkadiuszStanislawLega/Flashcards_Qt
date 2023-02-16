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
    query.exec((create_table_questions))
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
    QString create_table_questions_tags = "create table if not exists QuestionsTags"
              "(id integer primary key autoincrement not null,"
              "Question_id integer not null,"
              "Tag_id integer not null,"
              "foreign key (Question_id) references Questions(Id),"
              "foreign key (Tag_id) references Tags(Id));";
    query.exec(create_table_questions_tags);
}
