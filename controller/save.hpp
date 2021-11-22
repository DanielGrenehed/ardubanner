#ifndef SAVE_HPP
#define SAVE_HPP

#include <vector>
#include <string>

bool writeLinesToFile(std::vector<std::string> lines, std::string filename);

std::vector<std::string> loadLinesFromFile(std::string filename);

#endif /* ifndef SAVE_HPP */