#include "learnview.h"

#include <stringmanager.h>

LearnView::LearnView(QWidget *parent) : QWidget{parent}, ui(new Ui::LearnView) {
  this->ui->setupUi(this);
  this->ui->l_answer->setText("");
  this->ui->l_value->setText("");
  this->ui->pb_answers->setValue(0);
  this->initialTagListView();
  this->_correct_answer = 0;
  this->_uncorrect_answer = 0;
  this->_is_answer_was_visible = false;
}

LearnView::~LearnView() { qDeleteAll(this->_randomised_questions); }

void LearnView::initialTagListView() {
  this->_tags_model = new QSqlRelationalTableModel;
  this->_tags_model->setTable(StringManager::get(StringID::TableTags));
  this->_tags_model->select();
  this->ui->cb_tags->setModel(this->_tags_model);
  this->ui->cb_tags->setModelColumn(this->_tags_model->record().indexOf(
      StringManager::get(StringID::ColumnTag)));
}

void LearnView::make_randomised_questions_list_new() {
  int i;
  QList<Question *> questions;
  TagAndQuestionRelationSql relation =
      TagAndQuestionRelationSql(this->_selected_tag, new Question(this), this);

  questions = relation.getRelatedActiveQuesitons();

  this->_max_questions_number = questions.size();
  this->ui->sb_questions_number->setMaximum(this->_max_questions_number);
  this->ui->sb_questions_number->setValue(this->_max_questions_number);

  for (i = this->_max_questions_number; i > 0; i--) {
    long index = QRandomGenerator::global()->bounded(questions.size());
    this->_randomised_questions.push_back(
        new Question(questions[index]->getId(), questions[index]->getValue(),
                     questions[index]->getAnswer(), true, {}, this));

    questions.removeAt(index);
  }
  qDeleteAll(questions);
}

void LearnView::show_first_card_attribute() {
  if (this->ui->rb_answer->isChecked()) {
    this->set_answer();
  }

  if (this->ui->rb_question->isChecked()) {
    this->set_question();
  }

  if (this->ui->rb_random->isChecked()) {
    this->set_which_question_or_answer_show_first();
    this->show_answer_or_question();
  }
}

// Updates the view, the "value" property of the currently selected question.
void LearnView::set_question() {
  if (this->_randomised_questions.size()) {
    this->ui->l_value->setText(this->_randomised_questions.first()->getValue());
  }
}

// Updates the view, the "answer" property of the currently selected question.
void LearnView::set_answer() {
  if (this->_randomised_questions.size()) {
    this->ui->l_answer->setText(
        this->_randomised_questions.first()->getAnswer());
  }
}

void LearnView::set_which_question_or_answer_show_first() {
  this->_is_show_answer_first =
      QRandomGenerator::global()->bounded(0, 1000000) % 2 == 0;
}

void LearnView::show_answer_or_question() {
  if (this->_is_show_answer_first) {
    this->set_answer();
    this->_is_show_answer_first = false;
  } else {
    this->set_question();
    this->_is_show_answer_first = true;
  }
}

void LearnView::show_second_card_attribute() {
  if (this->ui->rb_answer->isChecked()) {
    this->set_question();
  }

  if (this->ui->rb_question->isChecked()) {
    this->set_answer();
  }

  if (this->ui->rb_random->isChecked()) {
    this->show_answer_or_question();
  }
}

void LearnView::action_after_set_points() {
  if (!this->_randomised_questions.size()) {
    return;
  }

  this->_randomised_questions.removeFirst();
  this->set_progress();
  this->clean_view();
}

void LearnView::set_progress() {
  this->set_progress_bar();
  this->set_questions_number();
}

void LearnView::set_progress_bar() {
  if (this->_randomised_questions.size() == 0) {
    this->ui->pb_answers->setValue(100);
    return;
  }

  float a, b, c;

  a = static_cast<float>(this->_max_questions_number -
                         this->_randomised_questions.size());
  b = static_cast<float>(this->_max_questions_number);
  c = a / b * 100;

  this->ui->pb_answers->setValue(c);
}

void LearnView::set_questions_number() {
  QString value = "";
  value += std::to_string(this->_max_questions_number -
                          this->_randomised_questions.size())
               .c_str();
  value += "/";
  value += std::to_string(this->_max_questions_number).c_str();
  this->ui->l_questions_counter->setText(value);
}

void LearnView::clean_view() {
  if (this->ui->rb_answer->isChecked()) {
    this->set_answer();
    this->ui->l_value->setText("");
  }

  if (this->ui->rb_question->isChecked()) {
    this->set_question();
    this->ui->l_answer->setText("");
  }

  if (this->ui->rb_random->isChecked()) {
    this->set_which_question_or_answer_show_first();
    this->_is_show_answer_first ? this->ui->l_value->setText("")
                                : this->ui->l_answer->setText("");
    this->show_answer_or_question();
  }
}

void LearnView::on_cb_tags_currentIndexChanged(int index) {
  int id, id_column, tag_column_index;
  QString tag;

  id_column = this->_tags_model->record().indexOf(
      StringManager::get(StringID::ColumnId));
  tag_column_index = this->_tags_model->record().indexOf(
      StringManager::get(StringID::ColumnTag));

  id = this->_tags_model->index(index, id_column).data(Qt::DisplayRole).toInt();
  tag = this->_tags_model->index(index, tag_column_index)
            .data(Qt::DisplayRole)
            .toString();

  this->_selected_tag = new Tag(id, tag, this);
}

void LearnView::on_b_start_clicked() {
  /*if (this->ui->sb_questions_number->value() == 0) {
    return;
  }*/

  this->ui->l_answer->setText("");
  this->ui->l_value->setText("");
  this->ui->pb_answers->setValue(0);

  this->_randomised_questions.clear();
  this->_max_questions_number = this->ui->sb_questions_number->value();
  this->make_randomised_questions_list_new();
  this->set_questions_number();

  this->show_first_card_attribute();
}

void LearnView::on_b_show_answer_clicked() {
  this->_is_answer_was_visible = true;
  this->show_second_card_attribute();
}

void LearnView::penalty_for_answer_does_not_seen() {
  if (!this->_is_answer_was_visible) {
    this->show_second_card_attribute();

    QApplication::processEvents();
    QThread::sleep(this->PENALTY_TIME_IN_SECOND);
  }
  this->_is_answer_was_visible = false;
}

void LearnView::on_b_correct_clicked() {
  if (!this->_randomised_questions.size()) {
    return;
  }

  this->penalty_for_answer_does_not_seen();

  this->_correct_answer++;
  this->ui->lcd_correct->display(this->_correct_answer);
  this->action_after_set_points();
}

void LearnView::on_b_uncorrect_clicked() {
  if (!this->_randomised_questions.size()) {
    return;
  }

  this->penalty_for_answer_does_not_seen();

  this->_uncorrect_answer++;
  this->ui->lcd_uncorrect->display(this->_uncorrect_answer);
  this->action_after_set_points();
}

void LearnView::added_question_to_db() { this->initialTagListView(); }

void LearnView::removed_question_from_db() { this->initialTagListView(); }

void LearnView::added_tag_to_db() { this->initialTagListView(); }

void LearnView::update_tag_in_db() { this->initialTagListView(); }

void LearnView::removed_tag_from_db() { this->initialTagListView(); }

void LearnView::create_relation() { this->initialTagListView(); }

void LearnView::remove_relation() { this->initialTagListView(); }
void LearnView::update_question() { this->initialTagListView(); }
