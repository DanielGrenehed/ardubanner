#include "display.hpp"
//


Display::Display(int columns, int rows, uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) : lines(new String[rows]), lineOffsets(new int[rows]), m_lcd(rs, enable, d4, d5, d6, d7) {
    this->cols = columns;
    this->rows = rows;
    m_lcd.begin(cols, rows);
    reset();
}

void Display::setLine(String msg, int row) {
    lines[row] = msg;
    lineOffsets[row] = 0;
}

void Display::reset() {
    for (int i = 0; i < rows; i++) {
        lines[i] = "";
    }
    resetScroll();
    clear();
}

void Display::clear() {
    m_lcd.clear();
}

void Display::update() {
    clear();
    for (int i = 0; i < rows; i++) {
      printLine(i);
    }
}

void Display::scroll() {
    for (int i = 0; i < rows; i++) {
      if (lines[i].length() > cols) {

        if (lineOffsets[i] >= (lines[i].length()-1)+spacing) lineOffsets[i] = 0;
        else lineOffsets[i] += 1;
        
      }
    }
}

bool Display::isScrollable() {
    for (int i = 0; i < rows; i++) {
      if (lines[i].length()  > cols) return true;
    }
    return false;
}

void Display::setWrapSpacing(int s) {
    spacing = s;
}
  

void Display::resetScroll() {
    for (int i = 0; i < rows; i++) {
      lineOffsets[i] = 0;
    }
}

void Display::printLine(int i) {
    int linelength = lines[i].length();
    int offset = lineOffsets[i];
     
    String line = lines[i].substring(offset);
      
    int spaces = spacing;
    if (offset > linelength) spaces = spacing - (offset - linelength);
    
    for (int j = 0; j < spaces; j++) line += " ";
    line += lines[i].substring(0, offset);
    
    m_lcd.setCursor(0, i);
    m_lcd.print(line); 
}
