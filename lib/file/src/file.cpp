#include "file.h"

#include <stdexcept>

File::File(std::string filename) : filename(filename) 
{
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
}


File::~File() {
    if (file.is_open()) { 
        file.close();
    }
}


void File::clear() {
    file.clear();
}

void File::writeLine(const std::string& line) {
    file << line << std::endl;
}