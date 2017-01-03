#ifndef GPIOPINIO_GPIOPIN_H
#define GPIOPINIO_GPIOPIN_H

#include <IO/ServerIO/ISendTrigger.h>
#include <IO/ServerIO/CDPSignalChannel.h>
#include <CDPSystem/Base/CDPSetting.h>

#include <atomic>

namespace ServerIO {
class IChannel;
}

namespace GPIOPinIO {

class GPIOPin: public ServerIO::CDPSignalChannel<bool>, public ServerIO::ISendTrigger
{
public:
    GPIOPin(short nr, bool inputGPIO);
    ~GPIOPin();

    bool Initialize();
    bool Deinitialize();    
    void Update();

    std::string GetNodeTypeName() const override;
    void FlagForSend() override;
    void SetDebugLevel(int level);
    int GetDebugLevel() const;

private:
    std::atomic_bool m_doWrite;
    short m_nr;
    bool m_inputGPIO;
    unsigned char m_valueGPIO;
    std::string m_valuePath;
    int m_debugLevel;
};

}

#endif
