#include "controller.h"

Controller::Controller(Model *model, View *view)
{
    this->_model = model;
    this->_view = view;
}

void Controller::show_app(){
    this->_view->show_app();
}
