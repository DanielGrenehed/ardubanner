#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include "message.h"

class MessageHandler {
private:
  Message messages[MAX_MESSAGES];
  int size = 0 , current = 0;
  unsigned long lastChange = 0;
  void nextMessage(unsigned long time);
public:
  const char* firstLine();
  const char* secondLine();
  Message* Message();
  bool isEmpty();
  int getSize();
  bool update(unsigned long time);
  void reset();
  bool addMessage(int time, char* l1, char* l2);
};

#endif /* ifndef MESSAGEHANDLER_HPP */