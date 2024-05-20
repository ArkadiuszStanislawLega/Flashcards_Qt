#ifndef RELATIONVIEW_H
#define RELATIONVIEW_H

#include "ui_relationview.h"
#include <Constants/strings.h>
#include <Database/SqlModels/tagandquestionrelationsql.h>
#include <Models/question.h>
#include <Models/tag.h>
#include <QSqlQueryModel>
#include <QSqlRelation>
#include <QSqlRelationalTableModel>
#include <QStringListModel>
#include <QWidget>

namespace Ui {
class RelationView;
}

class RelationView : public QWidget {
  Q_OBJECT
public:
  explicit RelationView(QWidget *parent = nullptr);

signals:
  void create_relation();
  void remove_relation();

public slots:
  void added_question_to_db();
  void remove_question_from_db();
  void update_question_from_db();
  void added_tag_to_db();
  void remove_tag_from_db();
  void update_tag_from_db();

private slots:
  void on_cb_tags_currentIndexChanged(int index);
  void on_lv_questions_clicked(const QModelIndex &index);
  void on_lv_question_tags_clicked(const QModelIndex &index);
  void on_b_create_relation_clicked();
  void on_b_remove_relation_clicked();

  void on_le_filter_textChanged(const QString &arg1);

private:
  Tag *_selected_tag_to_question_add, *_tag_from_selected_question;
  Question *_selected_question;

  Ui::RelationView *ui;
  QSqlRelationalTableModel *_questions_table_model, *_tags_combo_box_model,
      *_questions_tags_table_model;
  void initialQuestionsListView();
  void initialQuestionTagsListView();
  void initialTagsComboBox();
  void printInfo(const QString &, bool isError = false);
};

#endif // RELATIONVIEW_H
