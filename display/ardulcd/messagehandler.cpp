#include "messagehandler.hpp"
#include <string.h>

const char* MessageHandler::firstLine() {
    return messages[current].line1;
}
const char* MessageHandler::secondLine() {
    return messages[current].line2;
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
    lastChange = time;
}
bool MessageHandler::shouldUpdate(unsigned long time) {
    if (size == 0) return false;
    return (time > (lastChange + messages[current].displayTime));
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