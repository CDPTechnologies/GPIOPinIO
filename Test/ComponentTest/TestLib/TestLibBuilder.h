#ifndef TESTLIBBUILDER_H
#define TESTLIBBUILDER_H

#include <CDPSystem/Application/CDPBuilder.h>

class TestLibBuilder : public CDPBuilder
{
  public:
    TestLibBuilder(const char* pLibName,const char* pTimeStamp);
    virtual CDPComponent* CreateNewComponent(const std::string& type);
    virtual CDPObject* CreateNewObject(const std::string& type);
};

#endif
