#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "tree.hpp"

namespace huffman_compression {

    class Statistics {
    public:
        int tree_size;
        int text_size;
        int bytes_size;
        Statistics();

    };

    std::map<char, int> map_from_text(std::istream &stream, Statistics &statistics);

    int get_size(std::string file_in, const Tree& tree);

    void encode(std::string file_in, std::ostream& out, const Tree& tree, Statistics& statistics);

    void decode(std::istream &in, std::string file_out,Tree& tree, Statistics& statistics);

    void process_byte(bool byte, std::ostream &stream, Statistics& statistics);

}