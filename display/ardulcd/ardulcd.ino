#include "display.hpp"
#include "messagehandler.hpp"

#define BAUD 115200
#define led 13
#define INPUT_SIZE 100


#define DISPLAY_WIDTH 20
#define DISPLAY_HEIGHT 4

/*

Global variables

*/

Display disp(DISPLAY_WIDTH, DISPLAY_HEIGHT, 12, 11, 5, 4, 3, 2);
// Display disp(DISPLAY_WIDTH, DISPLAY_HEIGHT, lcd);
MessageHandler msghand;
unsigned long lastTime = 0;
char empty[]="";


/*

Setup

*/
void setup() {
  Serial.begin(BAUD);
  pinMode(led, OUTPUT);
  disp.setMessage(msghand.getMessage());
  disp.update();
}

void loop() {
  readSerial();
    
  updateDisplay();
}

void readSerial() {
  if (Serial.available() > 0) {
    char input[INPUT_SIZE + 1];
    byte size = Serial.readBytesUntil('\n', input, INPUT_SIZE);
    input[size] = 0; // Add the final 0 to end the C string

    if (size > 0) {
      msghand.addMessage(600, input, empty);
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
      if (!msghand.addMessage(time, token, str2));
    } else {
      if (!msghand.addMessage(time, token, empty));
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
  /// update display only when there is a new message to be displayed
  if (msghand.update(time)) {
    disp.setMessage(msghand.getMessage());
    disp.update();
  }
}

/* void printString(const char *str) {
  disp.setLine(str, 0);
  disp.update();
}

void blinkLED(int millis) {
  digitalWrite(led, HIGH);
  delay(millis);
  digitalWrite(led, LOW);
} */