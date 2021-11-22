#ifndef SAVE_HPP
#define SAVE_HPP

#include <vector>
#include <string>

/* Writes all lines as seperate lines in file, returns false if file failed to open */
bool writeLinesToFile(std::vector<std::string> lines, std::string filename);

/* Returns a vector of string containing all lines in file */
std::vector<std::string> loadLinesFromFile(std::string filename);

#endif /* ifndef SAVE_HPP */