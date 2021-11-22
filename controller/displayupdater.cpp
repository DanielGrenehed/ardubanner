#include "displayupdater.hpp"
#include <chrono>
#include <thread>
#include <sstream>

void ThreadData::setData(std::vector<TimedMessage>& newdata) {
    std::lock_guard<std::mutex> lock(mut);
    messages = newdata;
    updated = true;
}

bool ThreadData::hasUpdated() {
    std::lock_guard<std::mutex> lock(mut);
    bool upd = updated;
    updated = false;
    return upd;
}

const TimedMessage& ThreadData::getMessage(int index) const {
    std::lock_guard<std::mutex> lock(mut);
    return messages.at(index);
}

int ThreadData::getSize() const {
    std::lock_guard<std::mutex> lock(mut);
    return messages.size();
}

bool ThreadData::shouldStop() {
    std::lock_guard<std::mutex> lock(mut);
    return stopped;
}

void ThreadData::stop() {
    std::lock_guard<std::mutex> lock(mut);
    stopped = true;
}

static void sendMessage(std::string message, std::shared_ptr<Serial> out) {
    std::stringstream stream(message);
    std::string segment;
    int i = 0;
    while (std::getline(stream, segment, '|')) {

        std::string line = std::to_string(i) + ':' + segment + '\n';
        char temp[100];
        strcpy(temp,line.c_str());
        temp[line.size()+1] = 0;

        out->writeToPort(temp, line.size());
        i++;
    }
}

static void sleep(int seconds) { std::this_thread::sleep_for(std::chrono::seconds(seconds)); }

#define TIME std::chrono::system_clock::time_point
#define NOW std::chrono::system_clock::now()

void UpdateDisplay(std::shared_ptr<ThreadData> messages, std::shared_ptr<Serial> out) {
    int index = 0;
    TIME next_update = NOW;
    while (!messages->shouldStop()) {

        if (messages->getSize() == 0) {
            sleep(1);
            continue;
        }

        TIME time = NOW;

        if(messages->hasUpdated()) { 
            index = 0;
            next_update = time;
        } 
        
        if (time >= next_update) {
            const TimedMessage& msg = messages->getMessage(index);
            sendMessage(msg.message, out);
            next_update = time + std::chrono::seconds(msg.time);
            
            index++;
            if (index >= messages->getSize()) index = 0;
        }
        sleep(1);
        
    }
}