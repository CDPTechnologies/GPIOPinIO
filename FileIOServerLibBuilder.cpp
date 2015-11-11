/**
FileIOServerLibBuilder implementation.
*/
#include "FileIOServer.h"
#include "FileIOServerLibBuilder.h"

FileIOServerLibBuilder::FileIOServerLibBuilder(const char* libName, const char* timeStamp)
: CDPBuilder(libName, timeStamp)
{
}

CDPComponent* FileIOServerLibBuilder::CreateNewComponent(const std::string& type)
{
    if (type=="FileIOServer")
        return new FileIOServer;

    return nullptr;
}

CDPBaseObject* FileIOServerLibBuilder::CreateNewCDPOperator(const std::string& modelName, const std::string& type, const CDPPropertyBase* inputProperty)
{
  return nullptr;
}
