#ifndef MESSAGE_H
#define MESSAGE_H
#include "util.hpp"

typedef struct Message {
  int displayTime;
  char line1[MAX_STR_LEN], line2[MAX_STR_LEN]; 
} Message;

#endif /* ifndef MESSAGE_H */