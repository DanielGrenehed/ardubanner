#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <memory>
#include "serial.hpp"
#include "messaghandler.hpp"

class Menu {
private:
    std::vector<std::shared_ptr<Serial> > ports;
    MessageHandler msghand;

    void printMenu();

public:
    Menu(std::vector<std::shared_ptr<Serial> > ports) : ports(ports) {}

    void show();

protected:
    void addMessage();
    void updateSerial();
    void loadFromFile();
    void saveToFile();
};

#endif /* ifndef MENU_HPP */