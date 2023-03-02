#ifndef TAGVIEW_H
#define TAGVIEW_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QStringListModel>
#include "ui_tagview.h"
#include "../Models/tag.h"
#include "../Database/dbtag.h"
#include "../Constants/strings.h"

namespace Ui{
        class TagView;
}

class TagView : public QWidget
{
    Q_OBJECT
public:
    explicit TagView(QWidget *parent = nullptr);

signals:

private slots:
    void on_b_create_tag_clicked();
    void on_b_update_tag_clicked();
    void on_b_remove_tag_clicked();

private:
    Ui::TagView *ui;
    Tag *_selected_tag;
    QSqlRelationalTableModel *_table_model;
    void initialTagsListView();
};

#endif // TAGVIEW_H
