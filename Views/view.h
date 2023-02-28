#ifndef VIEW_H
#define VIEW_H

#include "../Models/model.h"
#include "mainwindow.h"
#include "Views/learnview.h"
#include "Views/questionview.h"
#include "Views/tagview.h"
#include "Views/relationview.h"

#include <QApplication>

class View
{
private:
    Model *_model;
    QApplication *_parent;
    void initialize_views();
    MainWindow _main_window;
    LearnView *_learn_view;
    QuestionView *_question_view;
    TagView *_tag_view;
    RelationView *_relation_view;

public:
    View(Model *, QApplication *);
    LearnView *getLearnView();
    QuestionView *getQeustionView();
    TagView *getTagView();
    RelationView *getRelationView();
    void show_app();
};

#endif // VIEW_H
