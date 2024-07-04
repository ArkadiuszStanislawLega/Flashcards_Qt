#include "nullpointertoquestionandtagexception.h"

#include <stringmanager.h>

NullPointerToQuestionAndTagException::NullPointerToQuestionAndTagException(
    const char *className, const char *methodName)
    : DefaultException(className, methodName) {}

const char *NullPointerToQuestionAndTagException::what() {
  return generateMessage(
      StringManager::get(StringID::ErrorPointerToTagAndQuestionEmpty)
          .toStdString()
          .c_str());
}
