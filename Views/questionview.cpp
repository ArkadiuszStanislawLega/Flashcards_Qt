#include "questionview.h"

QuestionView::QuestionView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::QuestionView)
{
    ui->setupUi(this);
}
