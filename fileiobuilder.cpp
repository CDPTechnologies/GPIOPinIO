/**
FileIOServerLibBuilder implementation.
*/
#include "fileioserver.h"
#include "fileiobuilder.h"

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

CDPBaseObject* FileIOServerLibBuilder::CreateNewCDPOperator(const std::string&, const std::string&, const CDPPropertyBase*)
{
  return nullptr;
}
