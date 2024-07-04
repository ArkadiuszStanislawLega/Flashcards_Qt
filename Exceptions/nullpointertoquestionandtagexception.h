#ifndef NULLPOINTERTOQUESTIONANDTAGEXCEPTION_H
#define NULLPOINTERTOQUESTIONANDTAGEXCEPTION_H

#include "defaultexception.h"

class NullPointerToQuestionAndTagException : DefaultException {
public:
  NullPointerToQuestionAndTagException(const char *className,
                                       const char *methodName);
  const char *what();
};

#endif // NULLPOINTERTOQUESTIONANDTAGEXCEPTION_H
