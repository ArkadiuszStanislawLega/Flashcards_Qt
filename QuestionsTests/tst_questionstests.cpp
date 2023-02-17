#include <QtTest>
#include "../Models/question.h"
#include "../Database/dbquestion.h"
#include "../Database/dbmanager.h"
#include "../Constants/strings.h"

class QuestionsTests : public QObject
{
    Q_OBJECT
    const QString test_value = "TEST";
    int question_id {0};

public:
    QuestionsTests();
    ~QuestionsTests();

private slots:
    void isCreate();
    void findId();
    void read();
    void isUpdate();
    void getAllQuestions();
    void isRemoved();
};

QuestionsTests::QuestionsTests()
{
    DbManager(DATABASE_NAME);
}

QuestionsTests::~QuestionsTests()
{

}

void QuestionsTests::isCreate()
{
    Question *q = new Question();
    q->set_answer(test_value);
    q->set_value(test_value);
    QVERIFY(DbQuestion::isCreate(q));
}

void QuestionsTests::findId(){
    this->question_id = DbQuestion::findId(test_value, test_value);
    QVERIFY(this->question_id > 0);
}

void QuestionsTests::read(){
    Question *q = DbQuestion::read(this->question_id);
    QCOMPARE(this->question_id, q->get_id());
    QCOMPARE(test_value, q->get_answer());
    QCOMPARE(test_value, q->get_value());
}

void QuestionsTests::isUpdate(){
    QString test_value_2 = "TEST2";
    Question *q = new Question(this->question_id, test_value, test_value, {});
    q->set_answer(test_value_2);
    q->set_value(test_value_2);

    QVERIFY(DbQuestion::isUpdate(q));

    q = DbQuestion::read(this->question_id);
    QCOMPARE(test_value_2, q->get_answer());
    QCOMPARE(test_value_2, q->get_value());
}

void QuestionsTests::getAllQuestions(){
    QCOMPARE(1, DbQuestion::getAllQuestions().size());
}

void QuestionsTests::isRemoved(){
    QVERIFY(DbQuestion::isRemoved(this->question_id));
}

QTEST_APPLESS_MAIN(QuestionsTests)

#include "tst_questionstests.moc"
