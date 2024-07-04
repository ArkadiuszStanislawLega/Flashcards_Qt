#include "answerisemptyexception.h"

#include <stringmanager.h>

AnswerIsEmptyException::AnswerIsEmptyException(const char *className,
                                               const char *methodName)
    : DefaultException(className, methodName) {}

const char *AnswerIsEmptyException::what() {
  return generateMessage(
      StringManager::get(StringID::ErrorPropertyAnswerIsEmpty)
          .toStdString()
          .c_str());
}
