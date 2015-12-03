#include "gpio.h"

#include <fstream>
#include <string>
#include <iostream>

#include <StudioAPI/CDPVariantValue.h>
#include <StudioAPI/NodeStream.h>
#include <IO/ServerIO/IChannel.h>
#include <IO/ServerIO/DeltaValidatorSendTrigger.h>

#include<fstream>
#include<ext/stdio_filebuf.h>

typedef std::basic_ofstream<char>::__filebuf_type buffer_t;
typedef __gnu_cxx::stdio_filebuf<char> io_buffer_t;
FILE* cfile_impl(buffer_t* const fb)
{
    return (static_cast<io_buffer_t* const>(fb))->file(); //type std::__c_file
}

using namespace FileIO;
using namespace CDP::StudioAPI;

const std::string SYSFS_GPIO_EXPORT = "/sys/class/gpio/export";
const std::string SYSFS_GPIO_UNEXPORT = "/sys/class/gpio/unexport";
const std::string SYSFS_GPIO = "/sys/class/gpio/gpio";
const std::string SYSFS_DIRECTION = "/direction";
const std::string SYSFS_VALUE = "/value";
const std::string GPIO_IN = "in";
const std::string GPIO_OUT = "out";

namespace {

FILE* cfile(const std::ofstream& ofs)
{
    return cfile_impl(ofs.rdbuf());
}

FILE* cfile(const std::ifstream& ifs)
{
    return cfile_impl(ifs.rdbuf());
}

template <typename T> bool write_value(const std::string& file, T value)
{
    std::ofstream ofs(file.c_str());
    if (ofs < 0)
        return false;

    ofs << value;
    ofs.close();
    return true;
}

bool writable(const std::string& file)
{
    std::ifstream infile(file);
        return infile.good();
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

GPIO::GPIO(short nr, bool inputGPIO)
 : m_doWrite(false)
 , m_nr(nr)
 , m_inputGPIO(inputGPIO)
{
    m_valuePath = SYSFS_GPIO + std::to_string(m_nr) + SYSFS_VALUE;
    SetDataPointer(&m_valueGPIO);
    RegisterValidator(new ServerIO::DeltaValidatorSendTrigger(this));
}

GPIO::~GPIO()
{
}

bool GPIO::Initialize()
{
    bool ok = write_value(SYSFS_GPIO_EXPORT, m_nr);
    std::string direction = SYSFS_GPIO + std::to_string(m_nr) + SYSFS_DIRECTION;
    for (int i = 0; i<10 && !writable(direction); ++i)
        OSAPISleep(10);

    OSAPISleep(100);
    ok = write_value(direction, m_inputGPIO?GPIO_IN:GPIO_OUT) && ok;
    return ok;
}

bool GPIO::Deinitialize()
{
    return write_value(SYSFS_GPIO_UNEXPORT, m_nr);
}

void GPIO::Update()
{
    if (m_inputGPIO)
        m_valueGPIO = read_bool(m_valuePath);
    else if (m_doWrite.exchange(false))
        write_bool(m_valuePath, m_valueGPIO);
}

std::string GPIO::GetNodeTypeName() const
{
    return "FileIO.GPIO";
}


void GPIO::FlagForSend()
{
    m_doWrite = true;
}
