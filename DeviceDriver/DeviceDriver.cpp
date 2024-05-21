#include "DeviceDriver.h"
#include <stdexcept>

class ReadFailException : public std::exception {

};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    auto firstResult = m_hardware->read(address);
    for (int i = 0; i < 4; i++)
    {
        if (firstResult != m_hardware->read(address))
            throw ReadFailException();
    }
    return firstResult;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}