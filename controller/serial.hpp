#ifndef SERIAL_HPP
#define SERIAL_HPP
#include <string>

#define ARDUINO_WAIT_TIME 2000
//#define MAX_DATA_LENGTH 255

class Serial {
public:
    virtual ~Serial() {};

    virtual int readFromPort(char *buffer, unsigned int buf_size) = 0;
    virtual bool writeToPort(const char *buffer, unsigned int buf_size) = 0;
    virtual bool isConnected() = 0;
    virtual void disconnect() = 0;
};

Serial* CreateSerialConnection(const char *portname);

#endif /* ifndef SERIAL_HPP */