#include "nullpointertotagexception.h"

#include <stringmanager.h>

NullPointerToTagException::NullPointerToTagException(const char *className,
                                                     const char *methodName)
    : DefaultException(className, methodName) {}

const char *NullPointerToTagException::what() {
  return generateMessage(StringManager::get(StringID::ErrorPointerToTagEmpty)
                             .toStdString()
                             .c_str());
}
