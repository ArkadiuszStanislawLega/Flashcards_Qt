#ifndef STRINGMANAGER_H
#define STRINGMANAGER_H

#include "Enums/StringID.h"
#include <QMap>
#include <QObject>

class StringManager : public QObject {
private:
  Q_OBJECT
  static QMap<StringID, QString> _stringMap;

public:
  const static QString get(StringID id);

signals:
};

#endif // STRINGMANAGER_H
