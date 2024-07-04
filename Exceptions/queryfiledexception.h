#ifndef QUERYFILEDEXCEPTION_H
#define QUERYFILEDEXCEPTION_H

#include "defaultexception.h"
#include <string>
#include <stringmanager.h>

class QueryFiledException : DefaultException {
public:
  QueryFiledException(const char *className, const char *methodName);
  const char *what();
};

#endif // QUERYFILEDEXCEPTION_H
