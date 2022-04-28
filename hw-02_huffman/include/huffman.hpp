#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "tree.hpp"

namespace huffman_compression {
    class HuffmanArchiver {

        Tree* local_tree;

        void process_byte(bool byte, std::ostream &stream);

        std::map<char, int> map_from_text(std::istream &stream, int &size);

    public:
        int tree_size = 0;
        int text_size = 0;
        int bytes_size = 0;

        void build(std::string file);

        HuffmanArchiver();

        HuffmanArchiver(const HuffmanArchiver& other);

        HuffmanArchiver& operator=(HuffmanArchiver other);

        ~HuffmanArchiver();

        void write_size(std::string file_in, std::ostream& out);

        void write_tree(std::ostream& out);

        void read_tree(std::istream& in);

        void encode(std::string file_in, std::ostream& out);

        void decode(std::istream &in, std::string file_out);
    };
}