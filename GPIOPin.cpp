#include "GPIOPin.h"

#include <fstream>
#include <string>
#include <iostream>

#include <IO/ServerIO/DeltaValidatorSendTrigger.h>

#include<fstream>

using namespace GPIOPinIO;
using namespace CDP::StudioAPI;

const std::string SYSFS_GPIO_EXPORT = "/sys/class/gpio/export";
const std::string SYSFS_GPIO_UNEXPORT = "/sys/class/gpio/unexport";
const std::string SYSFS_GPIO = "/sys/class/gpio/gpio";
const std::string SYSFS_DIRECTION = "/direction";
const std::string SYSFS_VALUE = "/value";
const std::string GPIO_IN = "in";
const std::string GPIO_OUT = "out";

namespace {

template <typename T> bool write_value(const std::string& file, T value)
{
    std::ofstream ofs(file.c_str());
    if (ofs < 0)
        return false;

    ofs << value;
    ofs.close();
    return true;
}

bool read_bool(const std::string& file)
{
    std::ifstream ofs(file.c_str());
    if (ofs < 0)
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
{
    m_valuePath = SYSFS_GPIO + std::to_string(m_nr) + SYSFS_VALUE;
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
    write_value(SYSFS_GPIO_EXPORT, m_nr);
    std::cout << "SysFS configure write "<<SYSFS_GPIO_EXPORT<<" "<<m_nr<<std::endl;
    std::string direction = SYSFS_GPIO + std::to_string(m_nr) + SYSFS_DIRECTION;
    std::cout << "SysFS configure write "<<direction<<" "<< (m_inputGPIO?GPIO_IN:GPIO_OUT) << std::endl;
    OSAPISleep(200);
    ok = write_value(direction, m_inputGPIO?GPIO_IN:GPIO_OUT);
    OSAPISleep(50);
    return ok;
}

bool GPIOPin::Deinitialize()
{
    return write_value(SYSFS_GPIO_UNEXPORT, m_nr);
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
