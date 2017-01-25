#ifndef GPIOPINIO_GPIOSERVER_H
#define GPIOPINIO_GPIOSERVER_H

#include <IO/IOServer.h>
#include <IO/ServerIO/ChannelManager.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <CDPSystem/Base/CDPProperty.h>

namespace GPIOPinIO {
class GPIOPin;

class GPIOServer : public IOServer, public OSAPIThread
{
public:
    GPIOServer();
    ~GPIOServer();

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    std::string GetNodeTypeName() const override;
    void FillNodeChildren(CDP::StudioAPI::NodeStream &serializer) const override;
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
    CDPProperty<std::string> BaseDirectory;
    ServerIO::ChannelManager* m_channelManager;
    std::vector<GPIOPinIO::GPIOPin*> m_gpios;
    bool m_deinitialized;
};

}

#endif
