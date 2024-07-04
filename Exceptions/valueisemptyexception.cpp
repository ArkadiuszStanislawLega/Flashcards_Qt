#include "valueisemptyexception.h"

ValueIsEmptyException::ValueIsEmptyException(const char *className,
                                             const char *methodName)
    : DefaultException(className, methodName) {}

const char *ValueIsEmptyException::what() {
  return generateMessage(StringManager::get(StringID::ErrorPropertyValueIsEmpty)
                             .toStdString()
                             .c_str());
}
