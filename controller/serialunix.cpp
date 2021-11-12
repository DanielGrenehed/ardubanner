// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include "serial.hpp"


class UnixSerial: public Serial {
private:
    int port;
    bool connected;

    void configurePort() {
        struct termios port_settings;
        tcgetattr(port, &port_settings);
        bzero(&port_settings, sizeof(port_settings));
        
        // set baud rate 
        cfsetispeed(&port_settings, B115200);
        cfsetospeed(&port_settings, B115200);
        
        port_settings.c_cflag |= ( CLOCAL | CREAD |  CS8);    // Configure the device : 8 bits, no parity, no control
        port_settings.c_iflag |= ( IGNPAR | IGNBRK );
        port_settings.c_cc[VTIME]=0;                          // Timer unused
        port_settings.c_cc[VMIN]=0;                           // At least on character before satisfy reading
             
        if (tcsetattr(port, TCSANOW, &port_settings) == -1) {
            printf("failed to set port flags");
            disconnect();
        }
        
    }

    void openPort(const char *portname) {
        this->port = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
        
        if (port == -1) { 
            printf("open port fail %s\n", portname);
        } else {
            fcntl(port, F_SETFL, FNDELAY);
            printf("port opened\n");
            this->connected = true;
        }
    }

public:
    UnixSerial(const char *portname) {
        connected = false;
        openPort(portname);
        if (isConnected()) configurePort();
        if (isConnected()) sleep(ARDUINO_WAIT_TIME/1000);
    }

    ~UnixSerial() {
        disconnect();
    }

    int readFromPort(char *buffer, unsigned int buf_size) {
        return read(port, buffer, buf_size);
    }

    bool writeToPort(const char *buffer, unsigned int buf_size) {
        return write(this->port, buffer, buf_size);
    }

    bool isConnected() {
        return connected;
    }

    void disconnect() {
        if (this->isConnected()) {
            close(this->port);
            this->connected = false;
        }
    }
};



Serial* CreateSerialConnection(const char *portname) {
    UnixSerial *serial = new UnixSerial(portname);
    return serial;
}
