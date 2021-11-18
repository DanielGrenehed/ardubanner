#include "messagehandler.hpp"
#include <string.h>

const char* MessageHandler::firstLine() {
    return messages[current].line1;
}

const char* MessageHandler::secondLine() {
    return messages[current].line2;
}

const Message* MessageHandler::Message() {
    return &messages[current];
}

bool MessageHandler::isEmpty() {
    return size == 0;
}

int MessageHandler::getSize() {
    return size;
}

void MessageHandler::nextMessage(unsigned long time) {
    current++;
    if (current >= size) current = 0;
}

bool MessageHandler::update(unsigned long time) {
    if (size == 0) return false;
    if (size == 1 && lastChange == 0) {
        current = 0;
        lastChange = time;
        return true;
    }
    if (time >= (lastChange + messages[current].displayTime) && size > 1) {
        lastChange = time;
        nextMessage(time);
        return true;
    }
    return false;
}

void MessageHandler::reset() {
    size = 0;
    current = 0;
    lastChange = 0;
}

bool MessageHandler::addMessage(int time, char* l1, char* l2) {
    if (size+1 == MAX_MESSAGES || strlen(l1) > MAX_STR_LEN || strlen(l2) > MAX_STR_LEN) return false;
    messages[size].displayTime = time;
    strcpy(messages[size].line1, l1);
    strcpy(messages[size].line2, l2);
    size++;
    return true;
}