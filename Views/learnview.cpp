#include "learnview.h"

LearnView::LearnView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::LearnView)
{
    ui->setupUi(this);
}

void LearnView::testing(){
        ui->l_questions_counter->setText("costam");
}

void LearnView::on_b_start_clicked()
{

}

void LearnView::on_b_correct_clicked()
{

}

void LearnView::on_b_uncorrect_clicked()
{

}

void LearnView::on_b_show_answer_clicked()
{

}

