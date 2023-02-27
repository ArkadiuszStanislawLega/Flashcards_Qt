#ifndef RELATIONVIEW_H
#define RELATIONVIEW_H

#include <QWidget>
#include "ui_relationview.h"

namespace Ui{
        class RelationView;
}

class RelationView : public QWidget
{
    Q_OBJECT
public:
    explicit RelationView(QWidget *parent = nullptr);

signals:

private:
    Ui::RelationView *ui;
};

#endif // RELATIONVIEW_H
