#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include "util.hpp"

typedef struct Message {
  int displayTime;
  char line1[MAX_STR_LEN], line2[MAX_STR_LEN]; 
} Message;

#endif /* ifndef MESSAGE_HPP */