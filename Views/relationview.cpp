#include "relationview.h"

RelationView::RelationView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::RelationView)
{
    ui->setupUi(this);
}
