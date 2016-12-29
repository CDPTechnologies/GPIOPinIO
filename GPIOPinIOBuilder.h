/**
GPIOPinIOBuilder header file.
*/

#ifndef GPIOPINIO_GPIOPINIOBUILDER_H
#define GPIOPINIO_GPIOPINIOBUILDER_H

#include <CDPSystem/Application/CDPBuilder.h>

namespace GPIOPinIO {

class GPIOPinIOBuilder : public CDPBuilder
{
  public:
    GPIOPinIOBuilder(const char* libName,const char* timeStamp);
    CDPComponent* CreateNewComponent(const std::string& type) override;
    CDPBaseObject* CreateNewCDPOperator(const std::string& modelName,const std::string& type,const CDPPropertyBase* inputProperty) override;
};

}

#endif
