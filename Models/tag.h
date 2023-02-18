#pragma once
#ifndef TAG
#define TAG
#include <QString>

#include "strings.h"
#include "question.h"

class Question;

class Tag{
	private:
		long _id;
        QString _tag;
	public:
		Tag();
        Tag(long, QString);

		long get_id();
        QString get_tag();

		void set_id(long);
        void set_tag(QString);
		bool is_question_already_related(Question *);
};
#endif
