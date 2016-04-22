#include "fileioserver.h"

#include <StudioAPI/NodeStream.h>

#include "gpio.h"

using namespace FileIO;

FileIOServer::FileIOServer()
    : m_channelManager(new ServerIO::ChannelManager(this))
    , m_deinitialized(false)
{
}

FileIOServer::~FileIOServer()
{
    delete m_channelManager;
}

void FileIOServer::Create(const char* fullName)
{
    CDPComponent:: Create(fullName);
}

void FileIOServer::CreateModel()
{
    CDPComponent::CreateModel();
}

void FileIOServer::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
}

std::string FileIOServer::GetNodeTypeName() const
{
    return "FileIOServer";
}

void FileIOServer::FillNodeChildren(CDP::StudioAPI::NodeStream &serializer) const
{
    IOServer::FillNodeChildren(serializer);
    auto list = m_channelManager->GetChannelList();
    serializer.StdContainerStreamer(list);
}

bool FileIOServer::IsCommProblem()
{
    return false;
}

void FileIOServer::Activate()
{
  if (m_deinitialized)
    for (auto gpio : m_gpios)
        gpio->Initialize();

  m_deinitialized = false;
  Start(CDPTHREAD_PRIORITY_ABOVE_NORMAL, m_shortName);
  IOServer::Activate();
}

void FileIOServer::Suspend()
{
    Stop();
    IOServer::Suspend();

    for (auto gpio : m_gpios)
        gpio->Deinitialize();

    m_deinitialized = true;
}

void FileIOServer::Main()
{
    while (!m_bStop)
    {
        m_channelManager->SynchronizeValuesIn();
        for (auto gpio : m_gpios)
            gpio->Update();
        m_channelManager->SynchronizeValuesOut();
        OSAPISleep(10);
    }
}

bool FileIOServer::HandleXMLElement(XMLElementEx *pEx)
{
    std::string strGPIO = "GPIO";
    const XMLString& currentElement = pEx->GetName();

    if(currentElement == "GPIOs") // this is just wrapper element for GPIO elements
        return false; //Call handleElement for childern also

    if(currentElement == strGPIO.c_str())
    {
        bool cdpInput = pEx->GetAttributeValue("Input");
        short number = pEx->GetAttributeValue("Nr");
        std::string name = pEx->GetAttributeValue("Name");
        GPIO* channel = new GPIO(number, !cdpInput);
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
