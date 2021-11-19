#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <memory>
#include <thread>
#include "serial.hpp"
#include "messagehandler.hpp"
#include "displayupdater.hpp"

class Menu {
private:
    std::vector<std::shared_ptr<Serial> > ports;
    MessageHandler msghand;
    std::vector<std::shared_ptr<DisplayUpdater> > updaters;
    std::vector<std::thread> threads;

    void printMenu();

public:
    Menu(std::vector<std::shared_ptr<Serial> > ports);

    ~Menu();
    void show();

protected:
    void addMessage();
    void updateSerial();
    void loadFromFile();
    void saveToFile();
};

#endif /* ifndef MENU_HPP */