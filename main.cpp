#include "Models/model.h"
#include "Views/view.h"
#include "Controllers/controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application (argc, argv);
    Model *model = new Model();
    View *view = new View(model , &application);
    Controller *controller = new Controller(model , view);

    controller->show_app();
    return application.exec();
}
