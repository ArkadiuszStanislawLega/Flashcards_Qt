#ifndef VALUEISEMPTYEXCEPTION_H
#define VALUEISEMPTYEXCEPTION_H

#include "defaultexception.h"
#include <stringmanager.h>

class ValueIsEmptyException : DefaultException {
public:
  ValueIsEmptyException(const char *className, const char *methodName);
  const char *what();
};

#endif // VALUEISEMPTYEXCEPTION_H
