#pragma once
#ifndef TAG
#define TAG
#include <QString>
#include <QObject>
#include <QList>

#include "strings.h"
#include "question.h"
#include "../Database/DbCRUD.h"
#include "../Database/manytomany.h"

class Question;

class Tag : public QObject, public Db_crud<Tag>, public ManyToMany<Question>{
    private:
        Q_OBJECT
        int _id;
        QString _tag;

	public:
        Tag(QObject *parent = nullptr);
        Tag(QObject *parent = nullptr, int = 0, QString = "");

        int get_id();
        QString get_tag();

        void set_id(int);
        void set_tag(QString);
		bool is_question_already_related(Question *);

        // ManyToMany interface
        bool isRelationCreated(Question *);
        bool isRemovedRelation(Question *);
        QList<Question *> getAllRelated();
        bool isAllRelationRemoved();

        // Db_crud interface
        bool isCreate();
        Tag *isRead();
        bool isUpdate();
        bool isRemoved();
        int findId();
        QList<Tag *> getAll();
};
#endif
