#ifndef DEFAULTEXCEPTION_H
#define DEFAULTEXCEPTION_H

#include <exception>

class DefaultException : std::exception {
protected:
  const char *_className, *_methodName;
  const char *generateMessage(const char *info);

public:
  DefaultException(const char *className, const char *methodName);
};

#endif // DEFAULTEXCEPTION_H
