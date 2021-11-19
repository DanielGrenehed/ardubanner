#include "displayupdater.hpp"
#include <chrono>
#include <thread>
#include <sstream>
#include <cstring>

void DisplayUpdater::setData(std::vector<TimedMessage>& newdata) {
    std::lock_guard<std::mutex> lock(mut);
    messages = newdata;
    updated = true;
}

bool DisplayUpdater::hasUpdated() {
    std::lock_guard<std::mutex> lock(mut);
    bool upd = updated;
    updated = false;
    return upd;
}

const TimedMessage& DisplayUpdater::getMessage(int index) const {
    std::lock_guard<std::mutex> lock(mut);
    return messages.at(index);
}

int DisplayUpdater::getSize() const {
    std::lock_guard<std::mutex> lock(mut);
    return messages.size();
}

bool DisplayUpdater::shouldStop() {
    std::lock_guard<std::mutex> lock(mut);
    return stopped;
}

void DisplayUpdater::stop() {
    std::lock_guard<std::mutex> lock(mut);
    stopped = true;
}

static void printMessage(std::string msg, std::shared_ptr<Serial> out) {
    std::stringstream test(msg);
    std::string segment;
    int i = 0;
    while(std::getline(test, segment, '|')) {
        std::string line = std::to_string(i) + ':' + segment + '\n';
        char temp[100];
        strcpy(temp,line.c_str());
        temp[line.size()+1] = 0;
        out->writeToPort(temp, line.size());
        i++;
    }
}

void UpdateDisplay(std::shared_ptr<DisplayUpdater> messages, std::shared_ptr<Serial> out) {
    int index = 0;
    std::chrono::system_clock::time_point next_update = std::chrono::system_clock::now();
    while (!messages->shouldStop()) {
        if (messages->getSize() == 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
        if(messages->hasUpdated()) { 
            index = 0;
            next_update = time;
        } 
        
        // only update when time has exeeded
        if (time >= next_update) {
            const TimedMessage& msg = messages->getMessage(index);
         // print message
            printMessage(msg.msg, out);
            next_update = time + std::chrono::seconds(msg.time);
            
            index++;
            if (index >= messages->getSize()) index = 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
    }
}