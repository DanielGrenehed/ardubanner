#include "display.hpp"
//


Display::Display(int columns, int rows, int adress) : lines(new Line[rows]), lineOffsets(new int[rows]), m_lcd(adress, columns, rows) {
    this->cols = columns;
    this->rows = rows;
}

void Display::initDisplay(){
    m_lcd.begin();
    m_lcd.backlight();
    reset();
}

void Display::reset() {
    resetScroll();
    clear();
    char zero[]="";
    for (int i = 0; i < cols; i++) setLine(zero, i);
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
        if (strlen(lines[i].text) > cols) {
            if (lineOffsets[i] >= (strlen(lines[i].text)-1)+spacing) lineOffsets[i] = 0;
            else lineOffsets[i] += 1;
        }
    } 
}

bool Display::isScrollable() {
    for (int i = 0; i < rows; i++) {
        if (strlen(lines[i].text) > cols) return true;
    }
    return false;
}

void Display::setWrapSpacing(int s) {
    spacing = s;
}
  
bool Display::setLine(const char* text, int rw) {
    if (strlen(text) > MAX_STR_LEN || rw >= cols) return false;
    strcpy(lines[rw].text, text);
    lines[rw].text[MAX_STR_LEN-1] = 0;
    lineOffsets[rw] = 0;
}

void Display::resetScroll() {
    for (int i = 0; i < rows; i++) {
      lineOffsets[i] = 0;
    }
}

void Display::printLine(int i) {
    if (i >= cols) return;
    printMessage(lines[i].text, i);
}

void Display::printMessage(const char* line, int row) {
    char out[cols+1];
    out[cols] = 0;
    int pos= 0; 

    for (int i = lineOffsets[row]; pos < cols && i < strlen(line); i++) out[pos++] = line[i];
    if (lineOffsets[row] > 0) {
        int spaces = spacing;
        if (lineOffsets[row] > strlen(line)) spaces = spacing - (lineOffsets[row] - strlen(line));
        for (int i = 0; pos < cols && i < spaces; i++) out[pos++] = ' ';
        for (int i = 0; pos < cols && i < strlen(line); i++) out[pos++] = line[i];
    }
    for (;pos < cols;) out[pos++] = ' ';
    
    m_lcd.setCursor(0, row);
    m_lcd.printstr(out);
} 