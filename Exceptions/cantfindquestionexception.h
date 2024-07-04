#ifndef CANTFINDQUESTIONEXCEPTION_H
#define CANTFINDQUESTIONEXCEPTION_H

#include "defaultexception.h"

class CantFindQuestionException : DefaultException {
public:
  CantFindQuestionException(const char *className, const char *methodName);
  const char *what();
};

#endif // CANTFINDQUESTIONEXCEPTION_H
