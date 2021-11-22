#include "menu.hpp"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

static bool equal(char* a, char* b) {
    for(int i=0; a[i] != 0; i++) if(a[i] != b[i]) return false;
    return true;
}

static std::vector<std::shared_ptr<Serial> > getPorts(int argc, char **argv) {
    std::vector<std::shared_ptr<Serial> > ports;
    for (int i = 1; i < argc; i++) {
        bool found = false;
        for (int j = i-1; j > 1; j--) if (equal(argv[i], argv[j])) found = true;
        if (!found) {
            std::shared_ptr<Serial> port = CreateSerialConnection(argv[i]);
            if (port->isConnected()) ports.push_back(port);
        }
    }  
    return ports;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Not enough arguments\n");
        return -1;
    }
    std::vector<std::shared_ptr<Serial> > ports = getPorts(argc, argv);
    if (ports.size() > 0) {
        Menu menu(ports);
        menu.show(); 
    } else {
        std::cout << "No ports opened, exiting\n";
    }
   
}