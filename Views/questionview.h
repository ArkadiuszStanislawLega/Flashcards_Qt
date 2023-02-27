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
    void on_b_add_clicked();

    void on_b_update_clicked();

    void on_b_remove_clicked();

private:
    Ui::QuestionView *ui;
};

#endif // QUESTIONVIEW_H
