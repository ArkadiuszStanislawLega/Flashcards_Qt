#ifndef ANSWERISEMPTYEXCEPTION_H
#define ANSWERISEMPTYEXCEPTION_H

#include "defaultexception.h"

class AnswerIsEmptyException : DefaultException {
public:
  AnswerIsEmptyException(const char *className, const char *methodName);
  const char *what();
};

#endif // ANSWERISEMPTYEXCEPTION_H
