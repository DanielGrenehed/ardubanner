#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include "util.hpp"

struct Message {
  int displayTime;
  char line1[MAX_STR_LEN], line2[MAX_STR_LEN]; 
};


class MessageHandler {
private:
  Message messages[MAX_MESSAGES];
  int size = 0 , current = 0;
  unsigned long lastChange = 0;

public:
  const char* firstLine();
  const char* secondLine();
  bool isEmpty();
  int getSize();
  void nextMessage(unsigned long time);
  bool shouldUpdate(unsigned long time);
  void reset();
  bool addMessage(int time, char* l1, char* l2);
};

#endif /* ifndef MESSAGEHANDLER_HPP */