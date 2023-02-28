#ifndef LEARNVIEW_H
#define LEARNVIEW_H

#include <QWidget>
#include "ui_learnview.h"

namespace Ui{
        class LearnView;
}

class LearnView : public QWidget
{
    Q_OBJECT
public:
    explicit LearnView(QWidget *parent = nullptr);
    void testing();

signals:

private slots:
    void on_b_start_clicked();
    void on_b_correct_clicked();
    void on_b_uncorrect_clicked();
    void on_b_show_answer_clicked();

private:
    Ui::LearnView *ui;
};

#endif // LEARNVIEW_H
