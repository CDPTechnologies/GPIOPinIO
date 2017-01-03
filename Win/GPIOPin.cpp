#include "GPIOPin.h"

#include <fstream>
#include <string>
#include <iostream>

#include <IO/ServerIO/DeltaValidatorSendTrigger.h>

using namespace GPIOPinIO;
using namespace CDP::StudioAPI;

GPIOPin::GPIOPin(short, bool)
 : m_doWrite(false)
 , m_nr(0)
 , m_inputGPIO(false)
 , m_debugLevel(DEBUGLEVEL_NORMAL)
{
}

GPIOPin::~GPIOPin()
{
}

bool GPIOPin::Initialize()
{
    CDPMessage("%s does not have an implementation on this operating system.\n",
               GetNodeTypeName().c_str());
    return true;
}

bool GPIOPin::Deinitialize()
{
    return true;
}

void GPIOPin::Update()
{
}

std::string GPIOPin::GetNodeTypeName() const
{
    return "GPIOPinIO.GPIOPin";
}


void GPIOPin::FlagForSend()
{
}

void GPIOPin::SetDebugLevel(int level)
{
    m_debugLevel = level;
}

int GPIOPin::GetDebugLevel() const
{
    return m_debugLevel;
}
