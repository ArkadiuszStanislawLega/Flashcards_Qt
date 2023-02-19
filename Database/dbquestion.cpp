#include "dbquestion.h"

DbQuestion::DbQuestion()
{
}

bool DbQuestion::isCreate(Question *q){
        QSqlQuery query;

        query.prepare(INSERT + TABLE_QUESTIONS +
                     "(" + COLUMN_VALUE + ", " + COLUMN_ANSWER +
                       ")" + VALUES + "(:" + COLUMN_VALUE + ", :" + COLUMN_ANSWER + ")");

        query.bindValue(":" + COLUMN_VALUE, q->get_value());
        query.bindValue(":" + COLUMN_ANSWER, q->get_answer());

        return query.exec();
}

Question *DbQuestion::read(int id){
    Question *q = new Question();
    QSqlQuery query;
    query.prepare(SELECT + "* " + FROM + TABLE_QUESTIONS + " " +
                  WHERE + COLUMN_ID + " = (:" + COLUMN_ID + ") limit 1");
    query.bindValue(":" + COLUMN_ID, id);
    if (query.exec())
    {
       if (query.next())
       {
           int id, idValue, idAnswer;

           id = query.record().indexOf(COLUMN_ID);
           idValue = query.record().indexOf(COLUMN_VALUE);
           idAnswer = query.record().indexOf(COLUMN_ANSWER);

           q->set_id(query.value(id).toInt());
           q->set_answer(query.value(idAnswer).toString());
           q->set_value(query.value(idValue).toString());

           return q;
       }
    }
    return q;
}

int DbQuestion::findId(QString value, QString answer){
    QSqlQuery query;
    query.prepare(SELECT + "* " + FROM + TABLE_QUESTIONS + " " + WHERE +
                  COLUMN_VALUE + "=:" + COLUMN_VALUE + " " + AND +
                  COLUMN_ANSWER + "=:" + COLUMN_ANSWER);
    query.bindValue(":" + COLUMN_VALUE, value);
    query.bindValue(":" + COLUMN_ANSWER, answer);
    if(query.exec()){
        while(query.next()){
            int idColumn;
            idColumn = query.record().indexOf(COLUMN_ID);

            return query.value(idColumn).toInt();
        }
    }
    return -1;
}

bool DbQuestion::isUpdate(Question *q){
    QSqlQuery query;
    query.prepare(UPDATE + TABLE_QUESTIONS + " " + SET +
            COLUMN_VALUE + "=:" + COLUMN_VALUE + ", " +
            COLUMN_ANSWER + "=:" + COLUMN_ANSWER + " " +
            WHERE + COLUMN_ID + "=:" + COLUMN_ID);
    query.bindValue(":" + COLUMN_VALUE, q->get_value());
    query.bindValue(":" + COLUMN_ANSWER, q->get_answer());
    query.bindValue(":" + COLUMN_ID, q->get_id());
    return query.exec();
}

bool DbQuestion::isRemoved(int id){
    QSqlQuery query;
    query.prepare(DELETE + TABLE_QUESTIONS + " " + WHERE +
                  COLUMN_ID + "=:" + COLUMN_ID);
    query.bindValue(":" + COLUMN_ID, id);
    return query.exec();
}

vector<Question *> DbQuestion::getAllQuestions(){
   vector<Question *> questions;
   QSqlQuery query;
   query.prepare(SELECT + "* " + FROM + TABLE_QUESTIONS);

   if(query.exec()){
       while(query.next()){
           Question *q = new Question();
           int columnId, columnValue, columnAnswer;

           columnId = query.record().indexOf(COLUMN_ID);
           columnValue = query.record().indexOf(COLUMN_VALUE);
           columnAnswer = query.record().indexOf(COLUMN_ANSWER);

           q->set_id(query.value(columnId).toInt());
           q->set_answer(query.value(columnAnswer).toString());
           q->set_value(query.value(columnValue).toString());

           questions.push_back(q);
       }
   }

   return questions;
}

bool DbQuestion::isRelationCreated(Question *q, Tag *t){
    if (q != nullptr && t != nullptr)
    {
        QSqlQuery query;
        QString w = (INSERT + TABLE_QUESTIONS_TAGS + "(" + COLUMN_QUESTION_ID + ", " + COLUMN_TAG_ID  + ")" +
                       VALUES + "(:" + COLUMN_QUESTION_ID + ", :" + COLUMN_TAG_ID + ")");
        query.prepare(w);
        query.bindValue(":" + COLUMN_QUESTION_ID, q->get_id());
        query.bindValue(":" + COLUMN_TAG_ID, t->get_id());
        qDebug() << w;
        return query.exec();
    }
    return false;
}

bool DbQuestion::isRelationRemoved(Question *q, Tag *t){
    if (q != nullptr && t != nullptr)
    {

    }
    return false;
}

bool DbQuestion::isAllRelationRemoved(Question *q){
    if (q != nullptr){

    }
    return false;
}

vector<Tag *> readRelatedTags(Question *q){
    vector<Tag *> tags;
    if(q != nullptr){

    }
    return tags;
}

