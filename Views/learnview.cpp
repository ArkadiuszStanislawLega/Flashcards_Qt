#include "learnview.h"

void LearnView::initialTagListView(){
    QList<QString> cb_values;

    if(this->_max_question_number_in_tag.size() > 0){
        this->_max_question_number_in_tag.clear();
    }

    for(Tag *t : Tag::getAll()){
        int question_number =  t->getAllRelated().size();
        QString value = t->get_tag() + " [" + std::to_string(question_number).c_str() + "]";
        this->_tags_list.append(t);
        cb_values.append(value);
        this->_max_question_number_in_tag.append(question_number);
    }

    this->_tags_model->setStringList(cb_values);
    this->ui->cb_tags->setModel(this->_tags_model);
}

LearnView::LearnView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::LearnView){
    this->ui->setupUi(this);
    this->ui->l_answer->setText("");
    this->ui->l_value->setText("");
    this->_tags_model = new QStringListModel;
    this->initialTagListView();
    this->_current = nullptr;
    this->_correct_answer = 0;
    this->_uncorrect_answer = 0;
}

LearnView::~LearnView(){
    qDeleteAll(this->_tags_list);
    qDeleteAll(this->_randomised_questions);
    delete this->_current;
    qDeleteAll(this->_tags_list);
}

void LearnView::added_question_to_db(){
    this->initialTagListView();
}

void LearnView::removed_question_from_db(){
    this->initialTagListView();
}

void LearnView::added_tag_to_db(){
    this->initialTagListView();
}

void LearnView::update_tag_in_db(){
    this->initialTagListView();
}

void LearnView::removed_tag_from_db(){
    this->initialTagListView();
}

void LearnView::create_relation(){
    this->initialTagListView();
}

void LearnView::remove_relation(){
   this->initialTagListView();
}

void LearnView::on_b_start_clicked(){
   if(this->_selected_index >= this->_tags_list.size()){
        return;
   }

   if(this->ui->sb_questions_number->value() == 0){
        return;
   }

   this->ui->l_answer->setText("");
   this->ui->l_value->setText("");

   this->_randomised_questions.clear();
   this->_max_questions_number = this->ui->sb_questions_number->value();
   this->make_randomised_questions_list_new();

   this->_max_questions_number--;
   this->_current = this->_randomised_questions.at(this->_max_questions_number);
   this->set_value();
}

void LearnView::make_randomised_questions_list_new(){
   int i;
   QList<Question *> questions;
   questions = this->_tags_list.at(this->_selected_index)->getAllRelated();

   for(i = this->_max_questions_number; i > 0; i--){
        std::srand(time(NULL));
        long index = std::rand() % questions.size();

        this->_randomised_questions.push_back(questions.at(index));
        questions.removeAt(index);
   }
   qDeleteAll(questions);
}

void LearnView::select_questions(){
   if(this->_max_questions_number < 0 ||
       this->_max_questions_number >= this->_randomised_questions.size()){
        return;
   }

   this->_current = this->_randomised_questions.at(this->_max_questions_number);
   this->set_value();
}


void LearnView::set_value(){
   if(this->_current){
        this->ui->l_value->setText(this->_current->get_value());
   }
}

void LearnView::set_answer(){
   if(this->_current){
        this->ui->l_answer->setText(this->_current->get_answer());
   }
}

void LearnView::on_b_correct_clicked(){
   if(this->_max_questions_number < 0){
        return;
   }

   this->_correct_answer++;
   this->action_after_set_points();
}

void LearnView::on_b_uncorrect_clicked(){
   if(this->_max_questions_number < 0){
        return;
   }

   this->_uncorrect_answer++;
   this->action_after_set_points();
}

void LearnView::action_after_set_points(){
   this->select_questions();
   this->_max_questions_number--;
   this->select_questions();
   this->ui->l_answer->setText("");
}

void LearnView::on_b_show_answer_clicked(){
   this->set_answer();
}


void LearnView::on_cb_tags_currentIndexChanged(int index){
    this->ui->sb_questions_number->setMaximum(this->_max_question_number_in_tag[index]);
   this->_selected_index = index;

}
