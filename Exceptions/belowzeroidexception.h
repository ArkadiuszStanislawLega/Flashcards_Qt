#ifndef BELOWZEROIDEXCEPTION_H
#define BELOWZEROIDEXCEPTION_H

#include "defaultexception.h"

class BelowZeroIdException : DefaultException {
public:
  BelowZeroIdException(const char *className, const char *methodName);
  const char *what();
};

#endif // BELOWZEROIDEXCEPTION_H
