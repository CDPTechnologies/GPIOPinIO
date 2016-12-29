#ifndef GPIO_H
#define GPIO_H

#include <IO/ServerIO/ISendTrigger.h>
#include <IO/ServerIO/CDPSignalChannel.h>
#include <CDPSystem/Base/CDPSetting.h>

#include <atomic>

namespace ServerIO {
class IChannel;
}

namespace FileIO {

class GPIO: public ServerIO::CDPSignalChannel<bool>, public ServerIO::ISendTrigger
{
public:
    GPIO(short nr, bool inputGPIO);
    ~GPIO();

    bool Initialize();
    bool Deinitialize();    
    void Update();

    std::string GetNodeTypeName() const override;
    void FlagForSend() override;

private:
    std::atomic_bool m_doWrite;
    short m_nr;
    bool m_inputGPIO;
    unsigned char m_valueGPIO;
    std::string m_valuePath;
};

}

#endif
