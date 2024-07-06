#include "tagmodelsql.h"

#include <stringmanager.h>

#include <Exceptions/belowzeroidexception.h>
#include <Exceptions/cantfindquestionexception.h>
#include <Exceptions/nullpointertoqueryexception.h>
#include <Exceptions/nullpointertotagexception.h>
#include <Exceptions/queryfiledexception.h>
#include <Exceptions/valueisemptyexception.h>

TagModelSql::TagModelSql(Tag *model, QObject *parent) : QObject{parent} {
  this->_model = model;
}

void TagModelSql::convertQueryToTag(QSqlQuery *query) {
  if (!query) {
    throw NullPointerToQueryException(this->metaObject()->className(),
                                      "converterQueryToTag");
  }
  this->_model->setId(FromQueryToValueConverter::get<int>(
      query, StringManager::get(StringID::ColumnId)));
  this->_model->setTag(FromQueryToValueConverter::get<char *>(
      query, StringManager::get(StringID::ColumnTag)));
}

bool TagModelSql::isInsertedSql() {
  const char *methodName = "isInsertedSql";

  if (!this->_model) {
    throw NullPointerToTagException(this->metaObject()->className(),
                                    methodName);
  }

  InsertSql sql = InsertSql(StringManager::get(StringID::TableTags),
                            {StringManager::get(StringID::ColumnTag)}, this);
  QSqlQuery query;
  query.prepare(sql.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnTag),
                  this->_model->getTag());

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }
  return true;
}

bool TagModelSql::isDeleteSql() {
  const char *methodName = "isDeleteSql";

  if (!this->_model) {
    throw NullPointerToTagException(this->metaObject()->className(),
                                    methodName);
  }

  if (this->_model->getId() <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }
  DeleteSql queryS = DeleteSql(StringManager::get(StringID::TableTags),
                               {StringManager::get(StringID::ColumnId)}, this);

  QSqlQuery query;
  query.prepare(queryS.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId),
                  this->_model->getId());

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }
  return true;
}

bool TagModelSql::updateSql() {
  const char *methodName = "updateSql";
  if (!this->_model) {
    throw NullPointerToTagException(this->metaObject()->className(),
                                    methodName);
  }

  if (this->_model->getId() <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  UpdateSql sql = UpdateSql(StringManager::get(StringID::TableTags),
                            {StringManager::get(StringID::ColumnTag)}, this);

  QSqlQuery query;
  query.prepare(sql.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId),
                  this->_model->getId());
  query.bindValue(":" + StringManager::get(StringID::ColumnTag),
                  this->_model->getTag());
  qDebug() << query.lastQuery();

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }

  return true;
}

Tag *TagModelSql::selectTag(int id) {
  const char *methodName = "selectTag";
  if (id <= 0) {
    throw BelowZeroIdException(this->metaObject()->className(), methodName);
  }

  FindByKeySql *sql =
      new FindByKeySql(StringManager::get(StringID::TableTags), {}, this);
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId), id);

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }

  this->convertQueryToTag(&query);

  return this->_model;
}

Tag *TagModelSql::findByCriteria() {
  const char *methodName = "findByCriteria";
  if (this->_model->getTag().isEmpty()) {
    throw ValueIsEmptyException(this->metaObject()->className(), methodName);
  }
  QString criteria = StringManager::get(StringID::ColumnTag) +
                     "=:" + StringManager::get(StringID::ColumnTag);

  SelectWithCriteriaSql select = SelectWithCriteriaSql(
      StringManager::get(StringID::TableTags), {}, criteria, this);

  QSqlQuery query;
  query.prepare(select.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnTag),
                  this->_model->getTag());

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), methodName);
  }

  if (!query.next()) {
    throw CantFindQuestionException(this->metaObject()->className(),
                                    methodName);
  }

  try {
    this->convertQueryToTag(&query);
  } catch (NullPointerToQueryException &e) {
    qWarning() << this->metaObject()->className() << methodName << e.what();
  }

  return this->_model;
}

QList<Tag *> TagModelSql::getAllTags() {
  SelectSql sql = SelectSql(StringManager::get(StringID::TableTags), {}, this);
  QSqlQuery query;
  query.prepare(sql.generate());

  if (!query.exec()) {
    throw QueryFiledException(this->metaObject()->className(), "getAllTags");
  }
  QList<Tag *> tags;
  while (query.next()) {
    tags.push_back(FromQueryToTagConverter::get(&query));
    tags.back()->setParent(this);
  }
  return tags;
}
