#include "dbrelationquestiontag.h"

DbRelationQuestionTag::DbRelationQuestionTag()
{

}

bool DbRelationQuestionTag::isRelationCreated(Question *q, Tag *t){
    if (q != nullptr && t != nullptr){
        QSqlQuery query;
        query.prepare(INSERT + TABLE_QUESTIONS_TAGS + "(" + COLUMN_QUESTION_ID + ", " + COLUMN_TAG_ID  + ")" +
                       VALUES + "(:" + COLUMN_QUESTION_ID + ", :" + COLUMN_TAG_ID + ")");
        query.bindValue(":" + COLUMN_QUESTION_ID, q->get_id());
        query.bindValue(":" + COLUMN_TAG_ID, t->get_id());
        return query.exec();
    }
    return false;
}

bool DbRelationQuestionTag::isRelationRemoved(Question *q, Tag *t){
    if (q != nullptr && t != nullptr){
        QSqlQuery query;
        query.prepare(	DELETE + TABLE_QUESTIONS_TAGS + " " +
                        WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=:" + COLUMN_QUESTION_ID + " " +
                        AND + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=:" + COLUMN_TAG_ID);
        query.bindValue(":" + COLUMN_QUESTION_ID, q->get_id());
        query.bindValue(":" + COLUMN_TAG_ID, t->get_id());
        return query.exec();
    }
    return false;
}

bool DbRelationQuestionTag::isAllRelationWithQuestionRemoved(Question *q){
    if (q != nullptr){
       QSqlQuery query;
       query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " +
                     WHERE + COLUMN_QUESTION_ID + "=:" + COLUMN_QUESTION_ID);
       query.bindValue(":" + COLUMN_QUESTION_ID, q->get_id());
       return query.exec();
    }
    return false;
}

bool DbRelationQuestionTag::isAllRelationWithTagRemoved(Tag *t){
    if(t != nullptr){
        QSqlQuery query;
        query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " +
                      WHERE + COLUMN_TAG_ID + "=:" + COLUMN_TAG_ID);
        query.bindValue(":" + COLUMN_TAG_ID, t->get_id());
        return query.exec();
    }
    return false;
}

vector<Tag *> DbRelationQuestionTag::readRelatedTags(Question *q){
    vector<Tag *> tags;
    if(q != nullptr){
        QSqlQuery query;
        query.prepare(	SELECT + TABLE_TAGS + "." + COLUMN_ID + ", " + COLUMN_TAG + " " + FROM + TABLE_TAGS + " " +
                        INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " +
                        INNER_JOIN + TABLE_QUESTIONS + " " + ON + TABLE_QUESTIONS + "." + COLUMN_ID + "=" + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + " " +
                        WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=:" + COLUMN_QUESTION_ID + ";");
        query.bindValue(":" + COLUMN_QUESTION_ID, q->get_id());
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
    }
    return tags;
}

vector<Question *> DbRelationQuestionTag::readRelatedQuestions(Tag *t){

}
