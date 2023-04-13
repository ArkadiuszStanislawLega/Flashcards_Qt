#include <QtTest>
#include "../Models/question.h"
#include "../Models/tag.h"
#include "../Database/dbmanager.h"
#include "../Constants/strings.h"

class DatabaseTests : public QObject
{
    Q_OBJECT
    const QString test_value = "TEST";
    int question_id {0};
    int tag_id {0};

public:
    DatabaseTests();
    ~DatabaseTests();

private slots:
    void isCreateQuestion();
    void findIdQuestion();
    void readQuestion();
    void isUpdateQuestion();
    void getAllQuestions();

    void isCreateTag();
    void isFindIdTag();
    void readTag();
    void isUpdateTag();
    void getAllTags();

    void isRelationCreated();
    void readAllRelatedQuestions();
    void readAllRelatedTags();

    void isRelationRemoved();
    void isAllRealtionWithQuestionRemoved();

    void isRelationWithTagRemoved();

    void isRemovedQuestion();
    void isRemovedTag();
};

DatabaseTests::DatabaseTests()
{
    DbManager();
}

DatabaseTests::~DatabaseTests()
{

}

void DatabaseTests::isCreateQuestion()
{
    Question *q = new Question(this);
    q->set_answer(test_value);
    q->set_value(test_value);
    QVERIFY(q->isCreate());

    delete q;
}

void DatabaseTests::findIdQuestion(){
    Question *q = new Question(this);
    q->set_answer(test_value);
    q->set_value(test_value);

    this->question_id = q->findId();
    QVERIFY(this->question_id > 0);

    delete q;
}

void DatabaseTests::readQuestion(){
    Question *q = new Question(this->question_id);
    QVERIFY(q->isRead());
    QCOMPARE(this->question_id, q->get_id());
    QCOMPARE(test_value, q->get_answer());
    QCOMPARE(test_value, q->get_value());

    delete q;
}

void DatabaseTests::isUpdateQuestion(){
    QString test_value_2 = "TEST2";
    Question *q = new Question(this->question_id, test_value, test_value, {});
    q->set_answer(test_value_2);
    q->set_value(test_value_2);

    QVERIFY(q->isUpdate());

    q->isRead();
    QCOMPARE(test_value_2, q->get_answer());
    QCOMPARE(test_value_2, q->get_value());

    delete q;
}

void DatabaseTests::getAllQuestions(){
    QVERIFY(Question::getAll().size() > 0);
}

void DatabaseTests::isRemovedQuestion(){
    Question *q = new Question(this->question_id);
    QVERIFY(q->isRemoved());

    delete q;
}

void DatabaseTests::isCreateTag(){
    Tag *t = new Tag();
    t->set_tag(test_value);
    QVERIFY(t->isCreate());

    delete t;
}

void DatabaseTests::isFindIdTag(){
    Tag *t = new Tag();
    t->set_tag(test_value);
    this->tag_id = t->findId();

    QVERIFY(this->tag_id > 0);

    delete t;
}

void DatabaseTests::readTag(){
    Tag *t = new Tag();
    t->set_id(this->tag_id);
    QVERIFY(t->isRead());

    QCOMPARE(this->tag_id, t->get_id());
    QCOMPARE(test_value, t->get_tag());

    delete t;
}

void DatabaseTests::isUpdateTag(){
    QString test_value_2 = "TEST2";
    Tag *t = new Tag(this->tag_id, test_value);
    t->set_tag(test_value_2);

    QVERIFY(t->isUpdate());

    t->isRead();

    QCOMPARE(test_value_2, t->get_tag());

    delete t;
}

void DatabaseTests::getAllTags(){
    QVERIFY(Tag::getAll().size() > 0);
}

void DatabaseTests::isRemovedTag(){
    Tag *t = new Tag();
    t->set_id(this->tag_id);

    QVERIFY(t->isRemoved());

    delete t;
}

void DatabaseTests::isRelationCreated(){
    Tag *t = new Tag(this->tag_id, test_value);
    Question *q = new Question(this->question_id, test_value, test_value, {});
    QVERIFY(t->isRelationCreated(q));

    delete q;
    delete t;
}

void DatabaseTests::readAllRelatedQuestions(){
    Tag *t = new Tag(this->tag_id, test_value);
    Question *q1, *q2;
    QString q1_value, q2_value;

    q1 = new Question();
    q2 = new Question();

    q1_value = "test1";
    q2_value = "test2";

    q1->set_answer(q1_value);
    q1->set_value(q1_value);

    q2->set_answer(q2_value);
    q2->set_value(q2_value);

    q1->isCreate();
    q2->isCreate();

    q1->set_id(q1->findId());
    q2->set_id(q2->findId());

    q1->isRelationCreated(t);
    q2->isRelationCreated(t);

    QVERIFY(t->getAllRelated().size() > 0);

    q1->isRemovedRelation(t);
    q2->isRemovedRelation(t);
    q1->isRemoved();
    q2->isRemoved();

    delete t;
    delete q1;
    delete q2;
}

void DatabaseTests::isRelationWithTagRemoved(){
    Tag *t;
    Question *q1, *q2;
    QString value1, value2;

    t = new Tag(this->tag_id, test_value);

    q1 = new Question();
    q2 = new Question();

    value1 = "q1";
    value2 = "q2";

    q1->set_answer(value1);
    q1->set_value(value1);

    q2->set_answer(value2);
    q2->set_value(value2);

    q1->isCreate();
    q2->isCreate();

    q1->findId();
    q2->findId();

    q1->isRelationCreated(t);
    q2->isRelationCreated(t);

    QVERIFY(t->isAllRelationRemoved());
    QVERIFY(q1->getAllRelated().size() == 0);
    QVERIFY(q2->getAllRelated().size() == 0);

    q1->isRemoved();
    q2->isRemoved();

    delete t;
    delete q1;
    delete q2;
}

void DatabaseTests::readAllRelatedTags(){
    Question *q = new Question(this->question_id, test_value, test_value, {});
    QVERIFY(q->getAllRelated().size() > 0);

    delete q;
}

void DatabaseTests::isRelationRemoved(){
    Tag *t = new Tag(this->tag_id, test_value);
    Question *q = new Question(this->question_id, test_value, test_value, {});
    QVERIFY(q->isRemovedRelation(t));

    delete t;
    delete q;
}

void DatabaseTests::isAllRealtionWithQuestionRemoved(){
    Question *q;
    Tag *t1, *t2;
    QString tag1, tag2;
    q = new Question(this->question_id, test_value, test_value, {});
    t1 = new Tag();
    t2 = new Tag();

    tag1 = "tag1";
    tag2 = "tag2";

    t1->set_tag(tag1);
    t2->set_tag(tag2);

    q->isRelationCreated(t1);
    q->isRelationCreated(t2);

    QVERIFY(q->isAllRelationRemoved());
    QVERIFY(q->getAllRelated().size() == 0);

    delete q;
    delete t1;
    delete t2;
}

QTEST_APPLESS_MAIN(DatabaseTests)
#include "tst_databasetests.moc"
