#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Views/view.h"
#include "../Models/model.h"
#include "../Models/question.h"
#include "../Database/dbquestion.h"

class Controller
{
    Model *_model;
    View *_view;
public:
    Controller(Model *, View *);
    void show_app();
};

#endif // CONTROLLER_H
