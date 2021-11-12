#include "serial.hpp"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Not enough arguments\n");
        return -1;
    }
    Serial* port = CreateSerialConnection(argv[1]);
    const char message[] = "ON:1000&ON:5000&ON:2000";
    if (port->isConnected()) {
        printf("writing to port\n");
        port->writeToPort(message, sizeof(message));
    }
  
    delete port;
}