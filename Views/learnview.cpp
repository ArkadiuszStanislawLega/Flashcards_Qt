#include "learnview.h"

LearnView::LearnView(QWidget *parent) : QWidget{parent}, ui(new Ui::LearnView) {
  this->ui->setupUi(this);
  this->ui->l_answer->setText("");
  this->ui->l_value->setText("");
  this->ui->pb_answers->setValue(0);
  this->_tags_model = new QStringListModel;
  this->initialTagListView();
  this->_correct_answer = 0;
  this->_uncorrect_answer = 0;
  this->_is_answer_was_visible = false;
}

LearnView::~LearnView() {
  qDeleteAll(this->_tags_list);
  qDeleteAll(this->_randomised_questions);
  qDeleteAll(this->_tags_list);
}

void LearnView::initialTagListView() {
  QList<QString> cb_values;

  if (this->_max_question_number_in_tag.size() > 0) {
    this->_max_question_number_in_tag.clear();
  }

  this->prepare_tags_list(cb_values);
  this->_tags_model->setStringList(cb_values);
  this->ui->cb_tags->setModel(this->_tags_model);
}

void LearnView::prepare_tags_list(QList<QString> &list) {
  for (Tag *t : Tag::getAll()) {
    int question_number = t->getAllActiveRelated().size();
    QString value =
        t->get_tag() + " [" + std::to_string(question_number).c_str() + "]";
    this->_tags_list.append(t);
    list.append(value);
    this->_max_question_number_in_tag.append(question_number);
  }
}

void LearnView::make_randomised_questions_list_new() {
  int i;
  QList<Question *> questions;
  questions = this->_tags_list.at(this->_selected_index)->getAllActiveRelated();

  for (i = this->_max_questions_number; i > 0; i--) {
    long index = QRandomGenerator::global()->bounded(questions.size());
    // std::srand(time(NULL));
    // long index = std::rand() % questions.size();

    this->_randomised_questions.push_back(questions.at(index));
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
    this->ui->l_value->setText(
        this->_randomised_questions.first()->get_value());
  }
}

// Updates the view, the "answer" property of the currently selected question.
void LearnView::set_answer() {
  if (this->_randomised_questions.size()) {
    this->ui->l_answer->setText(
        this->_randomised_questions.first()->get_answer());
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
  value += std::to_string(this->_max_questions_number).c_str();
  value += "/";
  value += std::to_string(this->_max_questions_number -
                          this->_randomised_questions.size())
               .c_str();

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
  this->ui->sb_questions_number->setMaximum(
      this->_max_question_number_in_tag[index]);
  this->ui->sb_questions_number->setValue(
      this->_max_question_number_in_tag[index]);
  this->_selected_index = index;
}

void LearnView::on_b_start_clicked() {
  if (this->_selected_index >= this->_tags_list.size()) {
    return;
  }

  if (this->ui->sb_questions_number->value() == 0) {
    return;
  }

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
    QThread::sleep(1);
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
