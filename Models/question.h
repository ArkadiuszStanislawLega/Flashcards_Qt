#pragma once
#ifndef QUESTION 
#define QUESTION
#include <iostream>
#include <vector>
#include <set>
#include <sqlite3.h>
#include <algorithm>

#include "tag.h"
#include "strings.h"

using std::string;
using std::vector;

class Tag;

class Question{
	private:
		static int read_related_tag(void *, int, char **, char **);
		string _value, _answer;
		long _id;
		vector<Tag*> _tags;

	public:
		Question();
		Question(long, string, string, vector<Tag*>);

		long get_id();
		string get_value();
		string get_answer();
		vector<Tag*> get_tags();
		bool is_tag_already_related(Tag *);

		void set_id(long);	
		void set_value(string);
		void set_answer(string);
		void set_tags(vector<Tag*>);
			
		string to_string();
};
#endif
