#include "GPIOServer.h"

#include <StudioAPI/NodeStream.h>

#include "GPIOPin.h"

using namespace GPIOPinIO;

GPIOServer::GPIOServer()
    : m_channelManager(new ServerIO::ChannelManager(this))
    , m_deinitialized(false)
{
}

GPIOServer::~GPIOServer()
{
    delete m_channelManager;
}

void GPIOServer::Create(const char* fullName)
{
    CDPComponent::Create(fullName);
    BaseDirectory.Create("BaseDirectory",this,CDPPropertyBase::e_Element,(CDPOBJECT_SETPROPERTY_HANDLER)nullptr,(CDPOBJECT_VALIDATEPROPERTY_HANDLER)nullptr);
}

void GPIOServer::CreateModel()
{
    CDPComponent::CreateModel();
}

void GPIOServer::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
}

std::string GPIOServer::GetNodeTypeName() const
{
    return "GPIOPinIO.GPIOServer";
}

void GPIOServer::FillNodeChildren(CDP::StudioAPI::NodeStream &serializer) const
{
    IOServer::FillNodeChildren(serializer);
    auto list = m_channelManager->GetChannelList();
    serializer.StdContainerStreamer(list);
}

bool GPIOServer::IsCommProblem()
{
    return false;
}

void GPIOServer::Activate()
{
  if (m_deinitialized)
    for (auto gpio : m_gpios)
        gpio->Initialize();

  m_deinitialized = false;
  Start(CDPTHREAD_PRIORITY_ABOVE_NORMAL, m_shortName);
  IOServer::Activate();
}

void GPIOServer::Suspend()
{
    Stop();
    IOServer::Suspend();

    for (auto gpio : m_gpios)
        gpio->Deinitialize();

    m_deinitialized = true;
}

void GPIOServer::Main()
{
    while (!Stopped())
    {
        m_channelManager->SynchronizeValuesIn();
        for (auto gpio : m_gpios)
            gpio->Update();
        m_channelManager->SynchronizeValuesOut();
        OSAPISleep(10);
    }
}

bool GPIOServer::HandleXMLElement(XMLElementEx *pEx)
{
    std::string strGPIO = "GPIOPin";
    const XMLString& currentElement = pEx->GetName();

    if(currentElement == "GPIOPins") // this is just wrapper element for GPIOPin elements
        return false; //Call handleElement for childern also

    if(currentElement == strGPIO.c_str())
    {
        bool cdpInput = pEx->GetAttributeValue("Input");
        short number = pEx->GetAttributeValue("Nr");
        std::string name = pEx->GetAttributeValue("Name");
        GPIOPin* channel = new GPIOPin(number, !cdpInput);
        channel->SetDebugLevel(GetDebugLevel());
        if (BaseDirectory != "")
            channel->setBaseDirectory(BaseDirectory);
        if (channel->Initialize())
        {
            channel->Create(name.c_str(), this);
            channel->Configure(pEx);
            channel->SetChannelParameters(cdpInput,0,0,0);

            m_channelManager->SetSyncGroupId(cdpInput, channel);
            m_channelManager->RegisterCDPChannel(channel);
            m_gpios.push_back(channel);
        }
        else
            delete channel;

        return true;
    }

    return CDPComponent::HandleXMLElement(pEx);
}
