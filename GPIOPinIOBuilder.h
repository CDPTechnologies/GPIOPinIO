/**
FileIOServerLibBuilder header file.
*/


#ifndef FILEIOSERVERLIBBUILDER_H
#define FILEIOSERVERLIBBUILDER_H


#include <CDPSystem/Application/CDPBuilder.h>

class FileIOServerLibBuilder : public CDPBuilder
{
  public:
    FileIOServerLibBuilder(const char* libName,const char* timeStamp);
    CDPComponent* CreateNewComponent(const std::string& type) override;
    CDPBaseObject* CreateNewCDPOperator(const std::string& modelName,const std::string& type,const CDPPropertyBase* inputProperty) override;
};

#endif // FILEIOSERVERLIBBUILDER_H
