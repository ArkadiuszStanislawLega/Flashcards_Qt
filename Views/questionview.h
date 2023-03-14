#ifndef QUESTIONVIEW_H
#define QUESTIONVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QSqlTableModel>
#include <QStringListModel>
#include <QSqlRelationalTableModel>
#include <QDebug>
#include "../Models/question.h"
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
    void added_question_to_db();

private slots:
    void on_b_update_question_clicked();
    void on_b_remove_question_clicked();
    void on_b_create_question_clicked();

    void on_lv_created_quesions_pressed(const QModelIndex &index);

private:
    Question *_selected_question;
    Ui::QuestionView *ui;
    QSqlRelationalTableModel *_table_model;
    void initialQuestionsListView();
    void cleanTextEditors();
    void printInfo(const QString &, bool);
};

#endif // QUESTIONVIEW_H
