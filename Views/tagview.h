#ifndef TAGVIEW_H
#define TAGVIEW_H

#include <QWidget>
#include "ui_tagview.h"

namespace Ui{
        class TagView;
}

class TagView : public QWidget
{
    Q_OBJECT
public:
    explicit TagView(QWidget *parent = nullptr);

signals:

private:
    Ui::TagView *ui;

};

#endif // TAGVIEW_H
