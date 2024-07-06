#include "nullpointertoqueryexception.h"

#include <stringmanager.h>

NullPointerToQueryException::NullPointerToQueryException(const char *className,
                                                         const char *methodName)
    : DefaultException(className, methodName) {}

const char *NullPointerToQueryException::what() {
  return generateMessage(StringManager::get(StringID::ErrorPointerToQueryEmpty)
                             .toStdString()
                             .c_str());
}
