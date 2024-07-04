#include "defaultexception.h"

#include <cstring>
#include <string>

const char *DefaultException::generateMessage(const char *info) {
  std::string temp{};
  temp = this->_className;
  temp += "::";
  temp += this->_methodName;
  temp += " -- ";

  return strstr(temp.c_str(), info);
}

DefaultException::DefaultException(const char *className,
                                   const char *methodName)
    : _className(className), _methodName(methodName) {}
