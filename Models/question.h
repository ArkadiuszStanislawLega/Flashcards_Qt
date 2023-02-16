#pragma once
#ifndef QUESTION 
#define QUESTION
#include <iostream>
#include <vector>
#include <set>
#include <sqlite3.h>
#include <algorithm>
#include <QString>

#include "tag.h"
#include "strings.h"

using std::vector;

class Tag;

class Question{
	private:
		static int read_related_tag(void *, int, char **, char **);
        QString _value, _answer;
		long _id;
		vector<Tag*> _tags;

	public:
		Question();
        Question(long, QString, QString, vector<Tag*>);

		long get_id();
        QString get_value();
        QString get_answer();
		vector<Tag*> get_tags();
		bool is_tag_already_related(Tag *);

		void set_id(long);	
        void set_value(QString);
        void set_answer(QString);
		void set_tags(vector<Tag*>);
			
        QString to_string();
};
#endif
