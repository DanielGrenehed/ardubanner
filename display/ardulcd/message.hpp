#ifndef MESSAGE_H
#define MESSAGE_H
#include "util.hpp"

struct Message {
  int displayTime;
  char line1[MAX_STR_LEN], line2[MAX_STR_LEN]; 
};

#endif /* ifndef MESSAGE_H */