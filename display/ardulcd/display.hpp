#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <LiquidCrystal_I2C.h>

#include "util.hpp"

typedef struct {
  char text[MAX_STR_LEN];
} Line;

class Display {
private:
  int cols, rows, spacing = 3;
  Line* lines;
  signed int* lineOffsets;
  LiquidCrystal_I2C m_lcd;

public:
  Display(int columns, int rows, int adress);

  void initDisplay();

  void reset();

  void clear();

  void update();

  void scroll();

  bool isScrollable();

  void setWrapSpacing(int s);

  bool setLine(const char* text, int rw);
  
private:
  void resetScroll();

  void printLine(int i);
  void printMessage(const char* line, int row);
};

#endif /* ifndef DISPLAY_HPP */
