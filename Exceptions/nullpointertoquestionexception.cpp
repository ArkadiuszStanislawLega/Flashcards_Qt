#include "nullpointertoquestionexception.h"
#include "qdebug.h"

NullPointerToQuestionException::NullPointerToQuestionException(
    const char *className, const char *methodName)
    : _className(className), _methodName(methodName) {}

const char *NullPointerToQuestionException::what() {
  std::string temp{};
  temp = this->_className;
  temp += this->_methodName;

  return strstr(temp.c_str(),
                StringManager::get(StringID::ErrorPointerToTagAndQuestionEmpty)
                    .toStdString()
                    .c_str());
}
