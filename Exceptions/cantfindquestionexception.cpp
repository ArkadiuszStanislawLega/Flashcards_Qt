#include "cantfindquestionexception.h"

#include <stringmanager.h>

CantFindQuestionException::CantFindQuestionException(const char *className,
                                                     const char *methodName)
    : DefaultException(className, methodName) {}

const char *CantFindQuestionException::what() {
  return generateMessage(StringManager::get(StringID::ErrorCantFindQuestion)
                             .toStdString()
                             .c_str());
}
