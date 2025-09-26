#ifndef CSV_FILE_H
#define CSV_FILE_H

#include <string>
#include <fstream>

class File {
    public:
        File(std::string filename);
        ~File();

        void clear();
        void writeLine(const std::string& line);

    private:
        std::string filename;
        std::ofstream file;
};

#endif