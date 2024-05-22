#include "dbmanager.h"

#include <stringmanager.h>

DbManager::DbManager() {
  this->_database = QSqlDatabase::addDatabase("QSQLITE");
  this->_database.setDatabaseName(StringManager::get(StringID::DatabaseName));

  if (!this->_database.open()) {
    qDebug() << StringManager::get(StringID::ErrorConnectionWithDatabase);
  } else {
    qDebug() << StringManager::get(StringID::ConnectionOk);
    this->CreateTables();
  }
}

DbManager::DbManager(const QString &path) {
  this->_database = QSqlDatabase::addDatabase("QSQLITE");
  this->_database.setDatabaseName(path);

  if (!this->_database.open()) {
    qDebug() << StringManager::get(StringID::ErrorConnectionWithDatabase);
  } else {
    qDebug() << StringManager::get(StringID::ConnectionOk);
    this->CreateTables();
  }
}

void DbManager::CreateTables() {
  this->CreateTableQuestions();
  this->CreateTableTags();
  this->CreateTableQuestionsTags();
}

void DbManager::CreateTableQuestions() {
  QSqlQuery query;
  query.prepare(CREATE_TABLE_IF_NOT_EXISTS +
                StringManager::get(StringID::TableQuestions) + "(" +
                StringManager::get(StringID::ColumnId) + " " + PRIMARY_KEY +
                ", " + StringManager::get(StringID::ColumnIsActive) + " " +
                INTEGER_NOT_NULL + " DEFAULT 1" + ", " +
                StringManager::get(StringID::ColumnValue) + " " + TEXT + ", " +
                StringManager::get(StringID::ColumnAnswer) + " " + TEXT + ")");
  query.exec();
}

void DbManager::CreateTableTags() {
  QSqlQuery query;
  query.prepare(
      CREATE_TABLE_IF_NOT_EXISTS + StringManager::get(StringID::TableTags) +
      "(" + StringManager::get(StringID::ColumnId) + " " + PRIMARY_KEY + ", " +
      StringManager::get(StringID::ColumnTag) + " " + TEXT + ")");
  query.exec();
}

void DbManager::CreateTableQuestionsTags() {
  QSqlQuery query;
  query.prepare(CREATE_TABLE_IF_NOT_EXISTS +
                StringManager::get(StringID::TableQuestionsTags) + "(" +
                StringManager::get(StringID::ColumnId) + " " + PRIMARY_KEY +
                ", " + StringManager::get(StringID::ColumnQuestionId) + " " +
                INTEGER_NOT_NULL + ", " +
                StringManager::get(StringID::ColumnTagId) + " " +
                INTEGER_NOT_NULL + "," + FOREIGN_KEY + "(" +
                StringManager::get(StringID::ColumnQuestionId) + ")" +
                REFERENCES + StringManager::get(StringID::TableQuestions) +
                "(" + StringManager::get(StringID::ColumnId) + ")" +
                FOREIGN_KEY + "(" + StringManager::get(StringID::ColumnTagId) +
                ")" + REFERENCES + StringManager::get(StringID::TableTags) +
                "(" + StringManager::get(StringID::ColumnId) + "))");
  query.exec();
}
