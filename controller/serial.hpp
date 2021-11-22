#ifndef SERIAL_HPP
#define SERIAL_HPP

#define ARDUINO_WAIT_TIME 2000
//#define MAX_DATA_LENGTH 255
#include <memory>

class Serial {
public:
    virtual ~Serial() {};

    /* Reads buf_size chars to buffer from serial port */
    virtual int readFromPort(char *buffer, unsigned int buf_size) = 0;

    /* Write buf_size chars from buffer to serial port */
    virtual bool writeToPort(const char *buffer, unsigned int buf_size) = 0;

    /* Returns true if connected to serial port */
    virtual bool isConnected() = 0;

    /* Closes serial connection */
    virtual void disconnect() = 0;
};

/* Returns a concrete serial connection to portname */
std::shared_ptr<Serial> CreateSerialConnection(const char *portname);

#endif /* ifndef SERIAL_HPP */