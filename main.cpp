#include "Constants/strings.h"
#include "Database/dbmanager.h"
#include "stringmanager.h"

#include <QApplication>
#include <QSettings>
#include <mainwindow.h>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  QCoreApplication::setOrganizationName("Arkadiusz Lega");
  QCoreApplication::setApplicationName("Fiszki");

  DbManager();

  QString settings_filename = application.applicationDirPath() + "/" +
                              StringManager::get(StringID::SettingsFilename);
  QSettings app_settings(settings_filename, QSettings::Format::IniFormat);
  app_settings.beginGroup("Version");
  app_settings.setValue("vs", 1);
  app_settings.endGroup();
  app_settings.sync();

  MainWindow w;
  w.show();

  return application.exec();
}
