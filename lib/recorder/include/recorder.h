#ifndef RECORDER_H
#define RECORDER_H

#include <string>
#include <memory>
#include <vector>
#include <cstddef>

class File;


class Recorder {
    public:
        Recorder(std::string output_filename, std::size_t data_rows, std::size_t columns);

        void record(const std::vector<std::string>& row);

        void save(File& file);

    private: 
        std::size_t getIndex(std::size_t row, std::size_t column);

        std::string output_filename;
        std::vector<std::string> buffer;
        std::size_t columns;
        std::size_t current_row;
    
};


#endif