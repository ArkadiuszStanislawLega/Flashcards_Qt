#pragma once
#ifndef QUESTION 
#define QUESTION
#include <iostream>
#include <set>
#include <sqlite3.h>
#include <QSqlQuery>
#include <algorithm>
#include <QString>
#include <QSqlRecord>
#include <QList>

#include "../Database/DbCRUD.h"
#include "../Database/manytomany.h"
#include "../Constants/strings.h"
#include "tag.h"
#include "strings.h"

class Tag;

class Question : public Db_crud<Question>, public ManyToMany<Tag>{
	private:
        int _id;
        QString _value, _answer;
        QList<Tag*> _tags;
        bool is_relation_valid(Tag *t);

	public:
        Question();
        Question(int);
        Question(int, QString, QString, QList<Tag*>);

        int get_id();
        QString get_value();
        QString get_answer();
        QList<Tag*> get_tags();
		bool is_tag_already_related(Tag *);

        void set_id(int);
        void set_value(QString);
        void set_answer(QString);
        void set_tags(QList<Tag*>);
			
        QString to_string();
        bool isCreate();
        Question *isRead();
        bool isUpdate();
        bool isRemoved();
        int findId();
        QList<Question *> getAll();

        bool isRelationCreated(Tag *);
        bool isRemovedRelation(Tag *);
        bool isAllRelationRemoved();
        QList<Tag *> getAllRelated();
};
#endif
