#include <QtTest>
#include "../Models/question.h"
#include "../Database/dbquestion.h"
#include "../Database/dbmanager.h"
#include "../Constants/strings.h"

class QuestionsTests : public QObject
{
    Q_OBJECT
    const QString test_value = "TEST";

public:
    QuestionsTests();
    ~QuestionsTests();

private slots:
    void isCreate();
    void read();
    void findId();
    void isUpdate();
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
    q->set_id(1);
    q->set_answer(test_value);
    q->set_value(test_value);
    QVERIFY(DbQuestion::isCreate(q));
}

void QuestionsTests::read(){
    Question *q = DbQuestion::read(1);
    QCOMPARE(1, q->get_id());
    QCOMPARE(test_value, q->get_answer());
    QCOMPARE(test_value, q->get_value());
}


void QuestionsTests::findId(){
    QCOMPARE(1, DbQuestion::findId(test_value, test_value));
}

void QuestionsTests::isUpdate(){
    QString test_value_2 = "TEST2";
    Question *q = new Question(1, test_value, test_value, {});
    q->set_answer(test_value_2);
    q->set_value(test_value_2);

    QVERIFY(DbQuestion::isUpdate(q));

    q = DbQuestion::read(1);
    QCOMPARE(test_value_2, q->get_answer());
    QCOMPARE(test_value_2, q->get_value());
}
QTEST_APPLESS_MAIN(QuestionsTests)

#include "tst_questionstests.moc"
