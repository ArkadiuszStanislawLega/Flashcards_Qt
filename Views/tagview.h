#ifndef TAGVIEW_H
#define TAGVIEW_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QStringListModel>
#include <QPalette>
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

    void on_lv_created_tags_clicked(const QModelIndex &index);

private:
    Ui::TagView *ui;
    Tag *_selected_tag;
    QSqlRelationalTableModel *_table_model;
    void initialTagsListView();
    void printInfo(const QString &, bool isError=false);
    void cleanTextEditors();
};

#endif // TAGVIEW_H
