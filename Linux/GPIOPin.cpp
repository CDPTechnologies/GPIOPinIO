#include "GPIOPin.h"

#include <fstream>
#include <string>

#include <IO/ServerIO/DeltaValidatorSendTrigger.h>

using namespace GPIOPinIO;
using namespace CDP::StudioAPI;

const std::string GPIO_BASE_DIR = "/sys/class/gpio";
const std::string SYSFS_GPIO_EXPORT = "/export";
const std::string SYSFS_GPIO_UNEXPORT = "/unexport";
const std::string SYSFS_GPIO = "/gpio";
const std::string SYSFS_DIRECTION = "/direction";
const std::string SYSFS_VALUE = "/value";
const std::string GPIO_IN = "in";
const std::string GPIO_OUT = "out";

namespace {

template <typename T> bool write_value(const std::string& file, T value)
{
    std::ofstream ofs(file.c_str());
    if (!ofs)
        return false;

    ofs << value;
    ofs.close();
    return true;
}

bool read_bool(const std::string& file)
{
    std::ifstream ofs(file.c_str());
    if (!ofs)
        return false;

    std::string value;
    ofs >> value;
    ofs.close();
    return value=="1";
}

void write_bool(const std::string& file, bool value)
{
    write_value(file, value?"1":"0");
}

}

GPIOPin::GPIOPin(short nr, bool inputGPIO)
  : m_doWrite(false)
  , m_nr(nr)
  , m_inputGPIO(inputGPIO)
  , m_debugLevel(DEBUGLEVEL_NORMAL)
  , m_baseDirectory(GPIO_BASE_DIR)
{
    composeValuePath();
    if (m_inputGPIO)
        SetDataPointer(&m_valueGPIO);
    RegisterValidator(new ServerIO::DeltaValidatorSendTrigger(this));
}

GPIOPin::~GPIOPin()
{
}

bool GPIOPin::Initialize()
{
    bool ok;
    write_value(m_baseDirectory + SYSFS_GPIO_EXPORT, m_nr);
    std::string direction = m_baseDirectory + SYSFS_GPIO + std::to_string(m_nr) + SYSFS_DIRECTION;
    if(m_debugLevel >= DEBUGLEVEL_EXTENDED)
    {
        CDPMessage("SysFS configure write to %s: \"%d\"\n",(m_baseDirectory + SYSFS_GPIO_EXPORT).c_str(), m_nr);
        CDPMessage("SysFS configure write to %s: \"%s\"\n", direction.c_str(), (m_inputGPIO?GPIO_IN:GPIO_OUT).c_str());
    }
    OSAPISleep(200);
    ok = write_value(direction, m_inputGPIO?GPIO_IN:GPIO_OUT);
    OSAPISleep(50);
    return ok;
}

bool GPIOPin::Deinitialize()
{
    return write_value(m_baseDirectory + SYSFS_GPIO_UNEXPORT, m_nr);
}

void GPIOPin::Update()
{
    if (m_inputGPIO)
        m_valueGPIO = read_bool(m_valuePath);
    else if (m_doWrite.exchange(false))
    {
        double ts;
        m_valueGPIO = this->GetInternal(ts);
        write_bool(m_valuePath, m_valueGPIO);
    }
}

std::string GPIOPin::GetNodeTypeName() const
{
    return "GPIOPinIO.GPIOPin";
}


void GPIOPin::FlagForSend()
{
    m_doWrite = true;
}

void GPIOPin::SetDebugLevel(int level)
{
    m_debugLevel = level;
}

int GPIOPin::GetDebugLevel() const
{
    return m_debugLevel;
}

std::string GPIOPin::baseDirectory() const
{
    return m_baseDirectory;
}

void GPIOPin::setBaseDirectory(const std::string& baseDirectory)
{
    m_baseDirectory = baseDirectory;
    composeValuePath();
}

void GPIOPin::composeValuePath()
{
    m_valuePath = m_baseDirectory + SYSFS_GPIO + std::to_string(m_nr) + SYSFS_VALUE;
}
