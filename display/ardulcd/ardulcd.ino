#include "display.hpp"

#define BAUD 115200
#define led 13
#define INPUT_SIZE 255

/*

Global variables

*/
const int displayLength = 16;
String textMsg = "";
Display disp(displayLength, 2, 12, 11, 5, 4, 3, 2);


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

void processInput(const char *input) {
  const char *delim = "&";
  // Read each command pair 
  char* command = strtok(input, delim);
  while (command != NULL) {
      // Split the command in two values
      char* separator = strchr(command, ':');
      if (separator != 0) {
          // Actually split the string in 2: replace ':' with 0
          *separator = 0;
          ++separator;
          int timeArg = atoi(separator);
          if (strcmp(command, "ON") == 0) {
            blinkLED(timeArg);
            delay(1000); //random delay number between commands.
          }
          // Do something with servoId and position
      }
      // Find the next command in input string
      command = strtok(NULL, delim);
  }
}

void updateDisplay() {
  if (disp.isScrollable() && millis() % 500 < 10) {
    disp.scroll();
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