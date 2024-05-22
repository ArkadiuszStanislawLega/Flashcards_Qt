#include "tagmodelsql.h"

#include <stringmanager.h>

TagModelSql::TagModelSql(Tag *model, QObject *parent) : QObject{parent} {
  this->_model = model;
}

void TagModelSql::convertQueryToTag(QSqlQuery *query) {
  if (!query) {
    throw std::invalid_argument(
        "TagModelSql::converterQueryToTag -- pointer to query is empty.");
  }
  this->_model->setId(FromQueryToValueConverter::get<int>(
      query, StringManager::get(StringID::ColumnId)));
  this->_model->setTag(FromQueryToValueConverter::get<char *>(
      query, StringManager::get(StringID::ColumnTag)));
}

bool TagModelSql::isInsertedSql() {
  if (!this->_model) {
    throw std::invalid_argument(
        "TagModelSql::isInsertedSql -- pointer to property model is empty.");
  }

  InsertSql sql = InsertSql(StringManager::get(StringID::TableTags),
                            {StringManager::get(StringID::ColumnTag)}, this);
  QSqlQuery query;
  query.prepare(sql.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnTag),
                  this->_model->getTag());

  if (!query.exec()) {
    throw std::invalid_argument("TagModelSql::isInsertedSql -- query failed.");
  }
  return true;
}

bool TagModelSql::isDeleteSql() {
  if (!this->_model) {
    throw std::invalid_argument(
        "TagModelSql::isDeleteSql -- pointer to tag is null.");
  }

  if (this->_model->getId() <= 0) {
    throw std::invalid_argument("TagModelSql::isDeleteSql -- property id "
                                "of the model is zero or below zero");
  }
  DeleteSql queryS = DeleteSql(StringManager::get(StringID::TableTags),
                               {StringManager::get(StringID::ColumnId)}, this);

  QSqlQuery query;
  query.prepare(queryS.generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId),
                  this->_model->getId());

  if (!query.exec()) {
    throw std::invalid_argument(
        "TagModelSql::isDeleteSql -- the query failed.");
  }
  return true;
}

bool TagModelSql::updateSql() {
  if (!this->_model) {
    throw std::invalid_argument(
        "TagModelSql::updateSql -- tag reference is empty.");
  }

  if (this->_model->getId() <= 0) {
    throw std::invalid_argument("TagModelSql::updateSql -- property id in "
                                "tag is zero or subzero.");
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
    throw std::invalid_argument("TagModelSql::updateSql -- the query failed.");
  }

  return true;
}

Tag *TagModelSql::selectTag(int id) {
  if (id <= 0) {
    throw std::invalid_argument(
        "TagModel::selectTag -- id is zero or subzero.");
  }

  FindByKeySql *sql =
      new FindByKeySql(StringManager::get(StringID::TableTags), {}, this);
  QSqlQuery query;
  query.prepare(sql->generate());
  query.bindValue(":" + StringManager::get(StringID::ColumnId), id);

  if (!query.exec()) {
    throw std::invalid_argument("TagMedelSql::selectTag -- the query failed.");
  }

  this->convertQueryToTag(&query);

  return this->_model;
}

Tag *TagModelSql::findByCriteria() {
  if (this->_model->getTag().isEmpty()) {
    throw std::invalid_argument(
        "TagModelSql::findByCriteria -- value is empty.");
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
    throw std::invalid_argument(
        "TagModelSql::findByCriteria - the query failed.");
  }

  if (!query.next()) {
    throw std::invalid_argument(
        "TagModelSql::findByCriteria - can't find question in database.");
  }

  try {
    this->convertQueryToTag(&query);
  } catch (std::invalid_argument &e) {
    qWarning() << "TagModelSql::findByCriteria -- " << e.what();
  }

  return this->_model;
}

QList<Tag *> TagModelSql::getAllTags() {
  SelectSql sql = SelectSql(StringManager::get(StringID::TableTags), {}, this);
  QSqlQuery query;
  query.prepare(sql.generate());

  if (!query.exec()) {
    throw std::invalid_argument("TagModelSql::getAllTags -- the query failed.");
  }
  QList<Tag *> tags;
  while (query.next()) {
    tags.push_back(FromQueryToTagConverter::get(&query));
    tags.back()->setParent(this);
  }
  return tags;
}
