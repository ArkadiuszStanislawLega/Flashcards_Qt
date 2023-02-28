#include "view.h"

View::View(Model *model, QApplication *parent)
{
    this->_model = model;
    this->_parent = parent;
    this->initialize_views();
}

LearnView *View::getLearnView(){
    return this->_learn_view;
}

QuestionView *View::getQeustionView(){
    return this->_question_view;
}

TagView *View::getTagView(){
    return this->_tag_view;
}

RelationView *View::getRelationView(){
    return this->_relation_view;
}

void View::initialize_views(){
    this->_learn_view = this->_main_window.findChild<LearnView *>("learn_view");
    this->_question_view = this->_main_window.findChild<QuestionView *>("question_view");
    this->_tag_view = this->_main_window.findChild<TagView *>("tag_view");
    this->_relation_view = this->_main_window.findChild<RelationView *>("relation_view");
}

void View::show_app(){
    this->_main_window.show();
    this->_learn_view->testing();
}
