#pragma once
#ifndef TAG
#define TAG
#include <QString>

#include "strings.h"
#include "question.h"

class Question;

class Tag{
	private:
        int _id;
        QString _tag;
	public:
		Tag();
        Tag(int, QString);

        int get_id();
        QString get_tag();

        void set_id(int);
        void set_tag(QString);
		bool is_question_already_related(Question *);
};
#endif
