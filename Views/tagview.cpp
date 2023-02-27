#include "tagview.h"

TagView::TagView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::TagView)
{
    ui->setupUi(this);
}
