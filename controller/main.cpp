#include "menu.hpp"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Not enough arguments\n");
        return -1;
    }
    std::vector<std::shared_ptr<Serial> > ports;
    for (int i = 1; i < argc; i++) {
        std::shared_ptr<Serial> port = CreateSerialConnection(argv[i]);
        ports.push_back(port);
    }  
    Menu menu(ports);

    menu.show();
    //std::shared_ptr<Serial> port = CreateSerialConnection(argv[1]);

    /*
    const char message[] = "ON:1000&ON:5000&ON:2000";
    if (port->isConnected()) {
        printf("writing to port\n");
        if (argc == 3) port->writeToPort(argv[2], strlen(argv[2]));
        else port->writeToPort(message, sizeof(message));
    }*/
}