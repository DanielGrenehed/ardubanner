#include "display.hpp"
//


Display::Display(int columns, int rows, uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) : lineOffsets(new int[rows]), m_lcd(rs, enable, d4, d5, d6, d7) {
    this->cols = columns;
    this->rows = rows;
    m_lcd.begin(cols, rows);
    reset();
}

void Display::setMessage(Message* msg) {
    message = msg;
    reset();
}

void Display::reset() {
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
    if (strlen(message->line1) > cols) {
        if (lineOffsets[0] >= (strlen(message->line1)-1)+spacing) lineOffsets[0] = 0;
        else lineOffsets[0] += 1;
    } 
    if (strlen(message->line2) > cols) {
        if (lineOffsets[1] >= (strlen(message->line2)-1)+spacing) lineOffsets[1] = 0;
        else lineOffsets[1] += 1;
    } 
}

bool Display::isScrollable() {
    if (strlen(message->line1) > cols) return true;
    if (strlen(message->line2) > cols) return true;
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
    if (i == 0) {
        printMessage(message->line1, i);
    } else if (i == 1) {
        printMessage(message->line2, i);
    }
    /* String cline = i == 0 ? message->line1 : message->line2;
    int linelength = cline.length();
    int offset = lineOffsets[i];
     
    String line = cline.substring(offset);
      
    int spaces = spacing;
    if (offset > linelength) spaces = spacing - (offset - linelength);
    
    for (int j = 0; j < spaces; j++) line += " "; // Add spaces
    line += cline.substring(0, offset);
    
    m_lcd.setCursor(0, i);
    if (i < 2) m_lcd.print(line); 
    else m_lcd.print(""); */
}

void Display::printMessage(const char* line, int row) {
    char out[cols+1];
    out[cols] = 0;
    int pos= 0; 

    for (int i = lineOffsets[row]; pos < cols && i < strlen(line); i++) out[pos++] = line[i];
    if (lineOffsets[row] > 0) {
        for (int i = 0; pos < cols && i < spacing; i++) out[pos++] = ' ';
        for (int i = 0; pos < cols && i < strlen(line); i++) out[pos++] = line[i];
    }
    for (;pos < cols;) out[pos++] = ' ';
    
    m_lcd.setCursor(0, row);
    m_lcd.print(out);
} 