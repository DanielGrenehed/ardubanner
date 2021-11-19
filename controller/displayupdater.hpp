#ifndef DISPLAYUPDATER_HPP
#define DISPLAYUPDATER_HPP

#include <mutex>
#include <string>
#include <vector>
#include "serial.hpp"

#include "timedmessage.hpp"

class DisplayUpdater {
private:
    bool updated;
    std::vector<TimedMessage> messages;
    bool stopped;
    mutable std::mutex mut;
public:
    DisplayUpdater() : updated(false), stopped(false){}

    void setData(std::vector<TimedMessage>& newdata);

    bool hasUpdated();

    const TimedMessage& getMessage(int index) const;
    int getSize() const;

    bool shouldStop();
    void stop();
};

void UpdateDisplay(std::shared_ptr<DisplayUpdater> messages, std::shared_ptr<Serial> out);

#endif /* ifndef DISPLAYUPDATER_HPP */