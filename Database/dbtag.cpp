#include "dbtag.h"

DbTag::DbTag()
{

}

bool DbTag::isCreate(Tag *t){
    if(t != nullptr){
       QSqlQuery query;

       query.prepare(INSERT + TABLE_TAGS +
                     "(" + COLUMN_TAG + ")" +
                     VALUES + "(:" + COLUMN_TAG + ")");

       query.bindValue(":" + COLUMN_TAG, t->get_tag());

       return query.exec();
    }
    return false;
}

int DbTag::findId(QString tag){
    if(tag != ""){

    }
    return -1;
}

Tag *DbTag::read(int id){
    Tag *tag = new Tag();
    if(id > 0){

    }
    return tag;
}

bool DbTag::isUpdate(Tag *t){
    if(t != nullptr){

    }
   return false;
}

bool DbTag::isRemoved(int id){
    if(id > 0){

    }
    return false;
}

int findId(QString tag){
    if (tag != nullptr)
    {

    }
    return -1;
}
