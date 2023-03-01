#ifndef QUESTIONVIEW_H
#define QUESTIONVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QSqlTableModel>
#include "../Models/question.h"
#include "../Database/dbquestion.h"
#include "../Constants/strings.h"
#include "ui_questionview.h"

using namespace std;

namespace Ui{
        class QuestionView;
}

class QuestionView : public QWidget
{
    Q_OBJECT
public:
    explicit QuestionView(QWidget *parent = nullptr);
signals:

private slots:
    void on_b_update_question_clicked();
    void on_b_remove_question_clicked();
    void on_b_create_question_clicked();

private:
    Ui::QuestionView *ui;
    QSqlTableModel *_table_model;
    void initialQuestionsListView();
};

#endif // QUESTIONVIEW_H
