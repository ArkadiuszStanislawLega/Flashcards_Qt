#include "belowzeroidexception.h"

#include <stringmanager.h>

BelowZeroIdException::BelowZeroIdException(const char *className,
                                           const char *methodName)
    : DefaultException(className, methodName) {}

const char *BelowZeroIdException::what() {
  return generateMessage(
      StringManager::get(StringID::ErrorPropertyIdInQuestionZero)
          .toStdString()
          .c_str());
}
