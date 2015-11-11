#ifndef FILEIOSERVER_H
#define FILEIOSERVER_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

class FileIOServer : public CDPComponent
{
public:
    FileIOServer();
    ~FileIOServer();

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* xml, const char* end = 0) override;

protected:
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

#endif

