#include "display.hpp"
#include "messagehandler.hpp"

#define BAUD 115200
#define led 13
#define INPUT_SIZE 100


#define DISPLAY_WIDTH 16
#define DISPLAY_HEIGHT 2

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
  //char cstr[16];
  //itoa(msghand.getSize(), cstr, 10);
  //printString(cstr);
  //blinkLED(10);
}

void readSerial() {
  if (Serial.available() > 0) {
    char input[INPUT_SIZE + 1];
    byte size = Serial.readBytesUntil('\n', input, INPUT_SIZE);
    input[size] = 0; // Add the final 0 to end the C string

    if (size > 0) {
      //printString(input);
      //delay(100);
      processInput(input);
    } 
  }
}

void processInput(char *input) {
  char* separator = strchr(input, ':');
    if (separator != 0) {
      *separator = 0; // Actually split the string in 2: replace ':' with 0
      ++separator; // Move pointer to time arg part of command
      int intArg = atoi(separator);
      if (strcmp(input, "U") == 0) {
        loadNewMessages(intArg);
      }
    } 
}

void loadNewMessages(int num) {
  msghand.reset();
  for (int i = 0; i < num; i++) readMessageFromSerial();
}

void readMessageFromSerial() {
  char input[INPUT_SIZE + 1];
  byte size = Serial.readBytesUntil('\n', input, INPUT_SIZE);
  input[size] = 0;

  char* token = strchr(input, ':');
  if (token != 0) {
    *token = 0; // end first part of input string
    ++token; 
    int time = atoi(input)*1000;
    char* str2 = strchr(token, '|');
    if (str2 != 0) {
      *str2 = 0;
      ++str2;
      if (!msghand.addMessage(time, token, str2)) printString("Failed to add message");
    } else {
      if (!msghand.addMessage(time, token, "")) printString("Faild to add message");
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



void nextMessage(unsigned long time) {
  if (msghand.shouldUpdate(time) && !msghand.isEmpty()) {
    msghand.nextMessage(time);
    disp.setLine(msghand.firstLine(), 0);
    disp.setLine(msghand.secondLine(), 1);
    disp.update();
  }
}

void printString(const char *str) {
  disp.setLine(str, 0);
  disp.update();
}

void blinkLED(int millis) {
  digitalWrite(led, HIGH);
  delay(millis);
  digitalWrite(led, LOW);
}