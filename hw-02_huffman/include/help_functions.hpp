#pragma once

#include "huffman.hpp"
#include<vector>
#include <istream>

std::vector <bool> read_bytes(std::istream& stream, size_t &calc_size);
