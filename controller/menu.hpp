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
    MessageHandler message_handler;
    std::vector<std::shared_ptr<Serial> > ports;
    std::vector<std::shared_ptr<ThreadData> > shared_data;
    std::vector<std::thread> threads;
public:
    Menu(std::vector<std::shared_ptr<Serial> > ports);
    ~Menu();

    /* Runs the menu loop prompting and responding to user input */
    void show();

protected:
    void addMessage();

    /* Deserializes messages from lines and adds them to message_handler */
    void addMessagesFromLines(std::vector<std::string> lines);

    /* Updates shared_data */
    void updateSerial();

    /* Prompts user for a filename and tries to load messages from it */
    void loadFromFile();

    /* Prompts user for a filename and tries to save messages to it */
    void saveToFile();

    /* Prints menu options to terminal */
    void printMenu();

    /* Prints serialized messages to terminal */
    void printMessages();
};

#endif /* ifndef MENU_HPP */