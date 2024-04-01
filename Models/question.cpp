#include "question.h"

Question::~Question(){
   qInfo() << "Destruction: " << this;
}

Question::Question(QObject *parent) : QObject(parent){
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
}

Question::Question(int id, QObject *parent)
    : Question(parent){
    this->_id = id;
}

Question::Question(int id, QString value, QString answer, QList<Tag*> tags, QObject *parent)
    : Question(id, parent){
	this->_value = value;
	this->_answer = answer;
	this->_tags = tags;
}

void Question::set_id(int value){
    this->_id = value;
}

QList<Tag*> Question::get_tags(){
	return this->_tags;
}

QString Question::get_value(){
	return this->_value;
}

QString Question::get_answer(){
	return this->_answer;
}

int Question::get_id(){
	return this->_id;
}

void Question::set_answer(QString value){
	this->_answer = value;
}

void Question::set_value(QString value){
	this->_value = value;
}

bool Question::is_tag_already_related(Tag *t){
	for(Tag *tag : this->_tags){
		if(tag->get_id() == t->get_id()){
			return true;
		}
	}
	return false;
}


QString Question::to_string(){
    return QString::number(this->_id) + ". " + this->_value + " " + this->_answer;
}

bool Question::isCreate()
{
    QSqlQuery query;

    query.prepare(INSERT + TABLE_QUESTIONS +
                 "(" + COLUMN_VALUE + ", " + COLUMN_ANSWER +
                   ")" + VALUES + "(:" + COLUMN_VALUE + ", :" + COLUMN_ANSWER + ")");

    query.bindValue(":" + COLUMN_VALUE, this->_value);
    query.bindValue(":" + COLUMN_ANSWER, this->_answer);

    return query.exec();
}

Question *Question::isRead()
{
    if (this->_id <= 0){
        return nullptr;
    }

    QSqlQuery query;
    query.prepare(SELECT + "* " + FROM + TABLE_QUESTIONS + " " +
                  WHERE + COLUMN_ID + " = (:" + COLUMN_ID + ") limit 1");
    query.bindValue(":" + COLUMN_ID, this->_id);

    if (!query.exec())
    {
        return nullptr;
    }

    if (!query.next())
    {
        return nullptr;
    }

    int id, idValue, idAnswer;

    id = query.record().indexOf(COLUMN_ID);
    idValue = query.record().indexOf(COLUMN_VALUE);
    idAnswer = query.record().indexOf(COLUMN_ANSWER);

    this->set_id(query.value(id).toInt());
    this->set_answer(query.value(idAnswer).toString());
    this->set_value(query.value(idValue).toString());

    return this;
}

bool Question::isUpdate()
{
    QSqlQuery query;
    query.prepare(UPDATE + TABLE_QUESTIONS + " " + SET +
            COLUMN_VALUE + "=:" + COLUMN_VALUE + ", " +
            COLUMN_ANSWER + "=:" + COLUMN_ANSWER + " " +
            WHERE + COLUMN_ID + "=:" + COLUMN_ID);
    query.bindValue(":" + COLUMN_VALUE, this->_value);
    query.bindValue(":" + COLUMN_ANSWER, this->_answer);
    query.bindValue(":" + COLUMN_ID, this->_id);
    return query.exec();
}

bool Question::isRemoved()
{
    QSqlQuery query;
    query.prepare(DELETE + TABLE_QUESTIONS + " " + WHERE +
                  COLUMN_ID + "=:" + COLUMN_ID);
    query.bindValue(":" + COLUMN_ID, this->_id);
    return query.exec();
}

int Question::findId()
{
    QSqlQuery query;
    query.prepare(SELECT + "* " + FROM + TABLE_QUESTIONS + " " + WHERE +
                  COLUMN_VALUE + "=:" + COLUMN_VALUE + " " + AND +
                  COLUMN_ANSWER + "=:" + COLUMN_ANSWER + " limit 1");
    query.bindValue(":" + COLUMN_VALUE, this->_value);
    query.bindValue(":" + COLUMN_ANSWER, this->_answer);

    if(!query.exec()){
        return -1;
    }

    if(query.next()){
        int idColumn;
        idColumn = query.record().indexOf(COLUMN_ID);
        this->_id = query.value(idColumn).toInt();

        return this->_id;
    }
    return -1;
}

bool Question::is_relation_valid(Tag *t){
    if(t == nullptr) return false;
    if(t->get_id() <= 0) return false;
    if(this->_id <= 0) return false;
    if(this->is_tag_already_related(t)) return false;

    return true;
}

bool Question::isRelationCreated(Tag *t)
{
   if(!this->is_relation_valid(t)){
       return false;
   }

   QSqlQuery query;
   query.prepare(INSERT + TABLE_QUESTIONS_TAGS + "(" + COLUMN_QUESTION_ID + ", " + COLUMN_TAG_ID  + ")" +
                  VALUES + "(:" + COLUMN_QUESTION_ID + ", :" + COLUMN_TAG_ID + ")");
   query.bindValue(":" + COLUMN_QUESTION_ID, this->_id);
   query.bindValue(":" + COLUMN_TAG_ID, t->get_id());
   return query.exec();
}

bool Question::isRemovedRelation(Tag *t)
{
    if(!this->is_relation_valid(t)){
       return false;
    }

    QSqlQuery query;
    query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " +
                    WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=:" + COLUMN_QUESTION_ID + " " +
                    AND + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=:" + COLUMN_TAG_ID);
    query.bindValue(":" + COLUMN_QUESTION_ID, this->_id);
    query.bindValue(":" + COLUMN_TAG_ID, t->get_id());
    return query.exec();
}

QList<Tag *> Question::getAllRelated()
{
    if(this->_id <= 0){
        return this->_tags;
    }

    QSqlQuery query;
    this->_tags.clear();

    query.prepare(SELECT + TABLE_TAGS + "." + COLUMN_ID + ", " + COLUMN_TAG + " " + FROM + TABLE_TAGS + " " +
                  INNER_JOIN + TABLE_QUESTIONS_TAGS + " " + ON + TABLE_QUESTIONS_TAGS + "." + COLUMN_TAG_ID + "=" + TABLE_TAGS + "." + COLUMN_ID + " " +
                  INNER_JOIN + TABLE_QUESTIONS + " " + ON + TABLE_QUESTIONS + "." + COLUMN_ID + "=" + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + " " +
                  WHERE + TABLE_QUESTIONS_TAGS + "." + COLUMN_QUESTION_ID + "=:" + COLUMN_QUESTION_ID);
    query.bindValue(":" + COLUMN_QUESTION_ID, this->_id);

    if(!query.exec()){
        return this->_tags;
    }

    while(query.next()){
        Tag *t = new Tag(this->parent());
        int idColumn, tagColumn;

        idColumn = query.record().indexOf(COLUMN_ID);
        tagColumn = query.record().indexOf(COLUMN_TAG);

        t->set_id(query.value(idColumn).toInt());
        t->set_tag(query.value(tagColumn).toString());

        this->_tags.append(t);
    }

    return this->_tags;
}

QList<Question *> Question::getAll()
{
    QList<Question *> questions;
    QSqlQuery query;
    query.prepare(SELECT + "* " + FROM + TABLE_QUESTIONS + " " + ORDER_BY + TABLE_QUESTIONS + "." + VALUES);

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

            questions.append(q);
        }
    }
    return questions;
}

bool Question::isAllRelationRemoved()
{
    if(this->_id <= 0){
        return false;
    }

    QSqlQuery query;
    query.prepare(DELETE + TABLE_QUESTIONS_TAGS + " " +
                  WHERE + COLUMN_QUESTION_ID + "=:" + COLUMN_QUESTION_ID);
    query.bindValue(":" + COLUMN_QUESTION_ID, this->_id);
    return query.exec();

}

void Question::set_tags(QList<Tag*> t){
	this->_tags = t;
}
