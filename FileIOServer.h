#ifndef FILEIOSERVER_H
#define FILEIOSERVER_H

#include <IO/IOServer.h>
#include <IO/ServerIO/ChannelManager.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

namespace FileIO {
class GPIO;
}

class FileIOServer : public IOServer, public OSAPIThread
{
public:
    FileIOServer();
    ~FileIOServer();

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* xml, const char* end = 0) override;
    std::string GetNodeTypeName() const override;
    void FillNodeChildren(CDP::StudioAPI::NodeStream &serializer) const override;
    int CalculateRegisterNumber(int moduleNo, int channelGroupNo, int channelNo, bool bDigitalChannel) override;
    bool IsCommProblem() override;
    void Activate() override;
    void Suspend() override;
    bool HandleXMLElement(XMLElementEx *pEx) override;

protected:
    void Main(void) override;

    using IOServer::m_shortName;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;

private:
    ServerIO::ChannelManager* m_channelManager;
    std::vector<FileIO::GPIO*> m_gpios;
    bool m_deinitialized;
};

#endif

