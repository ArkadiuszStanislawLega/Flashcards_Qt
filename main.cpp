#include "Constants/strings.h"
#include "Database/dbmanager.h"

#include <QApplication>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication application (argc, argv);
    DbManager(DATABASE_NAME);

    MainWindow w;
    w.show();

    return application.exec();
}
