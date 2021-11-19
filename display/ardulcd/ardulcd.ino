#include "display.hpp"
//#include "messagehandler.hpp"

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
//MessageHandler msghand;
unsigned long lastTime = 0;
//char empty[]="";


/*

Setup

*/
void setup() {
  Serial.begin(BAUD);
  pinMode(led, OUTPUT);
  //disp.setMessage(msghand.getMessage());
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
      //msghand.addMessage(600, input, empty);
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
      int intArg = atoi(input);
      disp.setLine(separator, intArg);
      disp.update();
    } 
}


void updateDisplay() {
  unsigned long time = millis();
  //nextMessage(time);
  if (disp.isScrollable() && time > lastTime + 500) {
    disp.scroll();
    disp.update();
    lastTime = time;
  }
}

