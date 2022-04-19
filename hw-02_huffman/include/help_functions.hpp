#pragma once

#include "huffman.hpp"
#include <vector>

std::vector <bool> read_bytes(std::istream &stream, size_t &calc_size);

void write_bytes(std::ostream &stream, std::vector<bool> bytes, size_t &calc_size);