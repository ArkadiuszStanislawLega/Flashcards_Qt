#include "tag.h"

Tag::Tag(){
	this->_id = 0;
	this->_tag = "";
}

Tag::Tag(int id, QString tag){
	this->_id = id;
	this->_tag = tag;
}

int Tag::get_id(){
	return this->_id;
}

QString Tag::get_tag(){
	return this->_tag;
}

void Tag::set_id(int id){
	this->_id = id;
}

void Tag::set_tag(QString tag){
	this->_tag = tag;
}

bool Tag::is_question_already_related(Question *q){
	for(Tag *t : q->get_tags()){
		if(t->get_id() == this->_id){
			return true;
		}
	}
	return false;
}
