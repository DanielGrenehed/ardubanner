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
        if (port->isConnected()) ports.push_back(port);
    }  
    Menu menu(ports);

    menu.show();
}