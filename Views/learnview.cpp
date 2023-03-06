#include "learnview.h"

void LearnView::initialTagListView()
{
    std:vector<Tag *> tags;
    QList<QString> cb_values;

    tags = DbTag::getAllTags();
    for(Tag *t : tags){
        QString value = t->get_tag() + " [" + std::to_string(DbRelationQuestionTag::readRelatedQuestions(t).size()).c_str() + "]";
        cb_values.append(value);
        qInfo() << value;
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

