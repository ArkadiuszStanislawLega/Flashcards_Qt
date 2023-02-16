#include "question.h"

void Question::set_id(long value){
	this->_id = value;
}

Question::Question(){
	this->_id = 0;
	this->_value = "";
	this->_answer = "";
}

Question::Question(long id, QString value, QString answer, vector<Tag*> tags){
	this->_id = id;
	this->_value = value;
	this->_answer = answer;
	this->_tags = tags;
}

vector<Tag*> Question::get_tags(){
	return this->_tags;
}

QString Question::get_value(){
	return this->_value;
}

QString Question::get_answer(){
	return this->_answer;
}

long Question::get_id(){
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

void Question::set_tags(vector<Tag*> t){
	this->_tags = t;
}
