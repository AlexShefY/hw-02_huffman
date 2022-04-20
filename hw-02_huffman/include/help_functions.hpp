#pragma once

#include "huffman.hpp"
#include <vector>

std::vector<bool> read_bytes(std::istream &stream, size_t &calc_size);

void write_bytes(std::ostream &stream, std::vector<bool> bytes, size_t &calc_size);

std::vector<char> read_text(std::istream &stream);

void write_text(std::ostream &stream, std::vector<char> text);

std::map<char, int> map_from_text(std::istream &stream, int &size);