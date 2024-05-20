#ifndef LEARNVIEW_H
#define LEARNVIEW_H

#include "ui_learnview.h"
#include <Constants/strings.h>
#include <Database/SqlModels/tagandquestionrelationsql.h>
#include <Database/SqlModels/tagmodelsql.h>
#include <Models/question.h>
#include <Models/tag.h>
#include <QRandomGenerator>
#include <QStringListModel>
#include <QThread>
#include <QWidget>

namespace Ui {
class LearnView;
}

class LearnView : public QWidget {

private:
  Q_OBJECT
  const int PENALTY_TIME_IN_SECOND = 1;
  Ui::LearnView *ui;
  QStringListModel *_tags_model;
  QList<Tag *> _tags_list;
  QList<Question *> _randomised_questions;
  int _selected_index, _correct_answer, _uncorrect_answer,
      _max_questions_number;
  bool _is_show_answer_first, _is_answer_was_visible;

  QList<unsigned int> _max_question_number_in_tag;

  void initialTagListView();
  void prepare_tags_list(QList<QString> &);
  void make_randomised_questions_list_new();
  void show_first_card_attribute();
  void set_question();
  void set_answer();
  void set_which_question_or_answer_show_first();
  void show_answer_or_question();
  void show_second_card_attribute();
  void penalty_for_answer_does_not_seen();
  void action_after_set_points();
  void set_progress();
  void set_progress_bar();
  void set_questions_number();
  void clean_view();

public:
  explicit LearnView(QWidget *parent = nullptr);
  ~LearnView();

signals:

public slots:
  void added_question_to_db();
  void removed_question_from_db();
  void added_tag_to_db();
  void update_tag_in_db();
  void removed_tag_from_db();
  void create_relation();
  void remove_relation();
  void update_question();

private slots:
  void on_cb_tags_currentIndexChanged(int index);
  void on_b_start_clicked();
  void on_b_correct_clicked();
  void on_b_uncorrect_clicked();
  void on_b_show_answer_clicked();
};

#endif // LEARNVIEW_H
