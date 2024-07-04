#include "queryfiledexception.h"

QueryFiledException::QueryFiledException(const char *className,
                                         const char *methodName)
    : DefaultException(className, methodName) {}

const char *QueryFiledException::what() {
  return generateMessage(
      StringManager::get(StringID::ErrorQueryFailed).toStdString().c_str());
}
