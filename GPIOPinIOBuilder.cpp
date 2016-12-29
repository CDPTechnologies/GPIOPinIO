/**
GPIOPinIOBuilder implementation.
*/
#include "GPIOServer.h"
#include "GPIOPinIOBuilder.h"

using namespace GPIOPinIO;

GPIOPinIOBuilder::GPIOPinIOBuilder(const char* libName, const char* timeStamp)
: CDPBuilder(libName, timeStamp)
{
}

CDPComponent* GPIOPinIOBuilder::CreateNewComponent(const std::string& type)
{
    if (type=="GPIOPinIO.GPIOServer")
        return new GPIOServer;

    return nullptr;
}

CDPBaseObject* GPIOPinIOBuilder::CreateNewCDPOperator(const std::string&, const std::string&, const CDPPropertyBase*)
{
  return nullptr;
}
