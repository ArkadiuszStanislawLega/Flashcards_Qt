#ifndef NULLPOINTERTOQUESTIONEXCEPTION_H
#define NULLPOINTERTOQUESTIONEXCEPTION_H

#include "defaultexception.h"

#include <stringmanager.h>

class NullPointerToQuestionException : DefaultException {
private:
  const char *_className, *_methodName;

public:
  NullPointerToQuestionException(const char *className, const char *methodName);
  const char *what();
};

#endif // NULLPOINTERTOQUESTIONEXCEPTION_H
