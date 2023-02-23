#include "view.h"

View::View(Model *model, QApplication *parent)
{
    this->_model = model;
    this->_parent = parent;
}

void View::show_app(){
    this->_main_window.show();
}
