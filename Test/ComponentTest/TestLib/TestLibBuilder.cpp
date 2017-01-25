#include "TestLibBuilder.h"

#include "ModelSource/GPIOPinIOLoopbackTest.h"

TestLibBuilder::TestLibBuilder(const char* pLibName,const char* pTimeStamp)
: CDPBuilder(pLibName,pTimeStamp)
{
}

CDPComponent* TestLibBuilder::CreateNewComponent(const std::string& type)
{
  if (type=="GPIOPinIOLoopbackTest")
    return new GPIOPinIOLoopbackTest;
  return nullptr;
}

CDPObject* TestLibBuilder::CreateNewObject(const std::string&)
{
  return NULL;
}
