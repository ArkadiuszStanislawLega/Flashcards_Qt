#include "nullpointertoquestionexception.h"
#include "qdebug.h"

NullPointerToQuestionException::NullPointerToQuestionException(
    const char *className, const char *methodName)
    : DefaultException(className, methodName) {}

const char *NullPointerToQuestionException::what() {
  return generateMessage(
      StringManager::get(StringID::ErrorPointerToTagAndQuestionEmpty)
          .toStdString()
          .c_str());
}
