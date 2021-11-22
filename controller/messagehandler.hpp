#ifndef MESSAGEHANDER_HPP
#define MESSAGEHANDER_HPP

//keybr.com
#include "message.hpp"
#include <vector>
#include "timedmessage.hpp"

class MessageHandler {
private:
    std::vector<Message> messages;
    int sum_paid;
public:
    MessageHandler(): sum_paid(0) {}

    /* Adds message to messages if ammount paid is enough to get shown */
    bool addMessage(Message m);

    /* Removes all messages with too low of ammount paid to get shown */
    void removeZeroTimeMessages();

    /* Removes all messages from message_handlers */
    void clear();
    
    /* Returns the messages in serialized form ("time:author:message") */
    std::vector<std::string> serialize();

    /* Returns the messages as timed messages */
    std::vector<TimedMessage> calculateTimedMessages();
};

#endif /* ifndef MESSAGEMANDLER_HPP */