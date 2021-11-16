#include "display.hpp"

#define BAUD 115200
#define led 13
#define INPUT_SIZE 255
#define MAX_MESSAGES 20

#define DISPLAY_WIDTH 16
#define DISPLAY_HEIGHT 2

class Message {
  public:
  int displayTime;
  char line1[MAX_STR_LEN], line2[MAX_STR_LEN]; 
};


class MessageHandler {
private:
  Message messages[MAX_MESSAGES];
  int size = 0 , current = 0;
  unsigned long lastChange = 0;

public:


  const char* firstLine() {
    return messages[current].line1;
  }
  const char* secondLine() {
    return messages[current].line2;
  }

  void nextMessage(unsigned long time) {
    current++;
    if (current >= size) current = 0;
    lastChange = time;
  }

  bool shouldUpdate(unsigned long time) {
    if (size == 0) return false;
    return time > (lastChange + messages[current].displayTime);
  }

  void reset() {
    size = 0;
    current = 0;
    lastChange = 0;
  }

  bool addMessage(int time, const char* l1, const char* l2) {
    if (size+1 == MAX_MESSAGES || strlen(l1) > MAX_STR_LEN || strlen(l2) > MAX_STR_LEN) return false;
    messages[size].displayTime = time;
    strcpy(l1, messages[size].line1);
    strcpy(l2, messages[size].line2);
    size++;
    return true;
  }
};
/*

Global variables

*/
Display disp(DISPLAY_WIDTH, DISPLAY_HEIGHT, 12, 11, 5, 4, 3, 2);

MessageHandler msghand;
unsigned long lastTime = 0;


/*

Setup

*/
void setup() {
  Serial.begin(BAUD);
  pinMode(led, OUTPUT);
  disp.update();
}

void loop() {
  readSerial();
    
  updateDisplay();

  blinkLED(10);
}

void readSerial() {
  if (Serial.available() > 0) {
    char input[INPUT_SIZE + 1];
    byte size = Serial.readBytes(input, INPUT_SIZE);
    input[size] = 0; // Add the final 0 to end the C string

    if (size > 0) {
      printString(input);
      processInput(input);
    } 
  }
}

void processInput(char *input) {
  const char *delim = "&";
  // Read each command pair 
  char* command = strtok(input, delim); // tokenize string for first command(command is a pointer to substring before first occurance of &)
  while (command != NULL) {
      // Split the command in two values
      char* separator = strchr(command, ':');
      if (separator != 0) {
         
          *separator = 0; // Actually split the string in 2: replace ':' with 0
          ++separator; // Move pointer to time arg part of command
          int intArg = atoi(separator);
          if (strcmp(command, "ON") == 0) { // 
            blinkLED(intArg);
            delay(1000); //random delay number between commands.
          } else if (strcmp(command, "U") == 0) {
            loadNewMessages(intArg);
          }
      }
      // Find the next command in input string
      command = strtok(NULL, delim);
  }
}

void loadNewMessages(int num) {
  msghand.reset();
  for (int i = 0; i < num; i++) readMessageFromSerial();
}

void readMessageFromSerial() {
  char input[INPUT_SIZE + 1];
  byte size = Serial.readBytes(input, INPUT_SIZE);
  input[size] = 0;

  char* token = strchr(input, ':');
  if (token != 0) {
    *token = 0; // end first part of input string
    token++; 
    int time = atoi(input);
    char* str2 = strchr(token, '|');
    if (str2 != 0) {
      *str2 = 0;
      str2++;
      msghand.addMessage(time, token, str2);
    } else {
      msghand.addMessage(time, token, "");
    }
  }

}
void updateDisplay() {
  unsigned long time = millis();
  nextMessage(time);
  if (disp.isScrollable() && time > lastTime + 500) {
    disp.scroll();
    disp.update();
    lastTime = time;
  }
}

void printString(const char *str) {
  disp.setLine(str, 0);
  disp.update();
}

void nextMessage(unsigned long time) {
  if (msghand.shouldUpdate(time)) {
    msghand.nextMessage(time);
    disp.setLine(msghand.firstLine(), 0);
    disp.setLine(msghand.secondLine(), 1);
    disp.update();
  }
}

void blinkLED(int millis) {
  digitalWrite(led, HIGH);
  delay(millis);
  digitalWrite(led, LOW);
}