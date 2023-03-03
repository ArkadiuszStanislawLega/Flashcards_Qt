#ifndef RELATIONVIEW_H
#define RELATIONVIEW_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include "../Models/question.h"
#include "../Models/tag.h"
#include "../Database/dbquestion.h"
#include "../Database/dbtag.h"
#include "../Database/dbrelationquestiontag.h"
#include "../Constants/strings.h"
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
    QSqlRelationalTableModel *_questions_table_model, *_tags_combo_box_model;
    void initialQuestionsListView();
    void initialTagsComboBox();
};

#endif // RELATIONVIEW_H
