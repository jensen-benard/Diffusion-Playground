#include "recorder.h"
#include "file.h"
#include <stdexcept>

Recorder::Recorder(std::string output_filename, std::size_t data_rows, std::size_t columns) : output_filename(output_filename), columns(columns) {
    buffer.reserve(data_rows * columns);

    for (std::size_t i = 0; i < data_rows * columns; i++) {
        buffer.push_back("0");
    }
}

std::size_t Recorder::getIndex(std::size_t row, std::size_t column) {
    return row * columns + column;
}


void Recorder::record(const std::vector<std::string>& row) {
    if(row.size() != columns) {
        throw std::runtime_error("Invalid row size: " + std::to_string(row.size()) + ", expected: " + std::to_string(columns));
    }
    for (std::size_t i = 0; i < columns; i++) {
        auto index = getIndex(current_row, i);
        buffer[index] = row[i];
    }
}


void Recorder::save(File& file) {
    for (const auto& line : buffer) {
        file.writeLine(line);
    }
}