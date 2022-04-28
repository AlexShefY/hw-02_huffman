#include <iostream>
#include <fstream>
#include "exceptions.hpp"
#include "huffman.hpp"
#include <string>

void encode(std::string file_in_name, std::string file_out_name, std::ostream& stream);

void decode(std::string file_in_name, std::string file_out_name, std::ostream& stream);