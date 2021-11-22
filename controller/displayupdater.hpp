#ifndef DISPLAYUPDATER_HPP
#define DISPLAYUPDATER_HPP

#include <mutex>
#include <string>
#include <vector>
#include "serial.hpp"

#include "timedmessage.hpp"

class ThreadData {
private:
    bool updated, stopped;
    std::vector<TimedMessage> messages;
    mutable std::mutex mut;

public:
    ThreadData() : updated(false), stopped(false) {}

    /* Replaces messages with newdata and sets updated to true */
    void setData(std::vector<TimedMessage>& newdata);

    /* Returns true if updated since last call to this function */
    bool hasUpdated();

    /* Returns a reference to message at index */
    const TimedMessage& getMessage(int index) const;

    /* Returns number of messages */
    int getSize() const;

    /* Returns stopped */
    bool shouldStop();

    /* Sets stopped to true */
    void stop();
};

/* Sends messages over serial sleeping for message-time. Occupies thread until thread_data.shouldStop() returns true */
void UpdateDisplay(std::shared_ptr<ThreadData> messages, std::shared_ptr<Serial> out);

#endif /* ifndef DISPLAYUPDATER_HPP */