#ifndef QUESTIONVIEW_H
#define QUESTIONVIEW_H

#include <QWidget>
#include "ui_questionview.h"

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
};

#endif // QUESTIONVIEW_H
