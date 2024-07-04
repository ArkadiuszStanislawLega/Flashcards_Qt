#ifndef NULLPOINTERTOTAGEXCEPTION_H
#define NULLPOINTERTOTAGEXCEPTION_H

#include "defaultexception.h"

class NullPointerToTagException : DefaultException {
public:
  NullPointerToTagException(const char *className, const char *methodName);
  const char *what();
};

#endif // NULLPOINTERTOTAGEXCEPTION_H
