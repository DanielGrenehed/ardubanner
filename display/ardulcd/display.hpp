#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <LiquidCrystal.h>

#include "message.h"

class Display {
private:
  int cols, rows, spacing = 3;
  signed int* lineOffsets;
  Message* message;
  LiquidCrystal m_lcd;

public:
  Display(int columns, int rows, uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

  void setMessage(Message* msg);

  void reset();

  void clear();

  void update();

  void scroll();

  bool isScrollable();

  void setWrapSpacing(int s);
  
private:
  void resetScroll();

  void printLine(int i);
  
};

#endif /* ifndef DISPLAY_HPP */