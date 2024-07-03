#ifndef NULLPOINTERTOQUESTIONEXCEPTION_H
#define NULLPOINTERTOQUESTIONEXCEPTION_H

#include <QException>
#include <stringmanager.h>

class NullPointerToQuestionException : std::exception {
private:
  const char *_className, *_methodName;

public:
  NullPointerToQuestionException(const char *className, const char *methodName);
  const char *what();
};

#endif // NULLPOINTERTOQUESTIONEXCEPTION_H
