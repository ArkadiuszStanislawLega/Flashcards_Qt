#ifndef NULLPOINTERTOQUERYEXCEPTION_H
#define NULLPOINTERTOQUERYEXCEPTION_H

#include "defaultexception.h"

class NullPointerToQueryException : DefaultException {
public:
  NullPointerToQueryException(const char *className, const char *methodName);
  const char *what();
};

#endif // NULLPOINTERTOQUERYEXCEPTION_H
