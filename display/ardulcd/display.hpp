#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <LiquidCrystal.h>

#include "util.hpp"

typedef struct {
  char text[MAX_STR_LEN];
} Line;

class Display {
private:
  int cols, rows, spacing = 3;
  Line* lines;
  signed int* lineOffsets;
  LiquidCrystal m_lcd;

public:
  Display(int columns, int rows, uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

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
