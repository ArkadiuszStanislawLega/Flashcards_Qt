#include "learnview.h"

void LearnView::initialTagListView()
{
    vector<Tag *> tags;
    QList<QString> cb_values;

    tags = DbTag::getAllTags();
    for(Tag *t : tags){
        int question_number = DbRelationQuestionTag::readRelatedQuestions(t).size();
        QString value = t->get_tag() + " [" + std::to_string(question_number).c_str() + "]";
        cb_values.append(value);
        this->_max_question_number_in_tag.append(question_number);
    }

    this->_tags_model->setStringList(cb_values);
    this->ui->cb_tags->setModel(this->_tags_model);
}

LearnView::LearnView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::LearnView)
{
    this->ui->setupUi(this);
    this->_tags_model = new QStringListModel;
    this->initialTagListView();
}

void LearnView::testing(){
        ui->l_questions_counter->setText("costam");
}

void LearnView::on_b_start_clicked()
{

}

void LearnView::on_b_correct_clicked()
{

}

void LearnView::on_b_uncorrect_clicked()
{

}

void LearnView::on_b_show_answer_clicked()
{
}


void LearnView::on_cb_tags_currentIndexChanged(int index)
{
    this->ui->sb_questions_number->setMaximum(this->_max_question_number_in_tag[index]);

}

