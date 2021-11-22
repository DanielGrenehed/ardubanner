#include "save.hpp"

#include <fstream>

bool writeLinesToFile(std::vector<std::string> lines, std::string filename) {
    std::ofstream myfile;
    myfile.open(filename, std::ios::trunc);
    if (myfile.is_open()) {
        for (int i = 0; i < lines.size(); i++) myfile << lines[i] + "\n";
        myfile.close();
        return true;
    }
    return false;
}

std::vector<std::string> loadLinesFromFile(std::string filename) {
    std::vector<std::string> lines;
    
    std::ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()) {
        std::string line;
        while (getline(myfile, line)) lines.push_back(line);
        myfile.close();
    }

    return lines;
}
