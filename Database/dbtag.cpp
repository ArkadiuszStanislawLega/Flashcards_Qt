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
        QSqlQuery query;
        query.prepare(SELECT + "* " + FROM + TABLE_TAGS + " " + WHERE +
                      COLUMN_TAG + "=:" + COLUMN_TAG);
        query.bindValue(":" + COLUMN_TAG, tag);
        if(query.exec()){
            while(query.next()){
               int idColumn;
               idColumn = query.record().indexOf(COLUMN_ID);

               return query.value(idColumn).toInt();
            }
        }
    }
    return -1;
}

Tag *DbTag::read(int id){
    Tag *tag = new Tag();
    if(id > 0){
        QSqlQuery query;
        query.prepare(SELECT + "* " + FROM + TABLE_TAGS + " " +
                      WHERE + COLUMN_ID + "=(:" + COLUMN_ID + ") limit 1");
        query.bindValue(":" + COLUMN_ID, id);

        if(query.exec()){
            if(query.next()){
                int idColumn, tagColumn;

                idColumn = query.record().indexOf(COLUMN_ID);
                tagColumn = query.record().indexOf(COLUMN_TAG);

                tag->set_id(query.value(idColumn).toInt());
                tag->set_tag(query.value(tagColumn).toString());

                return tag;
            }
        }
    }
    return tag;
}

bool DbTag::isUpdate(Tag *t){
    if(t != nullptr){
        QSqlQuery query;
        query.prepare(UPDATE + TABLE_TAGS + " " + SET +
                      COLUMN_TAG + "=:" + COLUMN_TAG + " " +
                      WHERE + COLUMN_ID + "=:" + COLUMN_ID);
        query.bindValue(":" + COLUMN_TAG, t->get_tag());
        query.bindValue(":" + COLUMN_ID, t->get_id());
        return query.exec();
    }
   return false;
}

vector<Tag *> DbTag::getAllTags(){
    vector<Tag *> tags;
    QSqlQuery query;
    query.prepare(SELECT + "* " + FROM + TABLE_TAGS);
    if(query.exec()){
        while(query.next()){
            Tag *t = new Tag();
            int idColumn, tagColumn;

            idColumn = query.record().indexOf(COLUMN_ID);
            tagColumn = query.record().indexOf(COLUMN_TAG);

            t->set_id(query.value(idColumn).toInt());
            t->set_tag(query.value(tagColumn).toString());

            tags.push_back(t);
        }
    }
    return tags;
}

bool DbTag::isRemoved(int id){
    if(id > 0){

    }
    return false;
}
