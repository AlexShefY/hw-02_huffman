#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "tree.hpp"

namespace HuffmanArchiver {
    class HuffmanArchiver {

        Trees::Tree* local_tree;

        void process_byte(bool byte, std::ostream &stream);

    public:
        int tree_size = 0;
        int text_size = 0;
        int bytes_size = 0;

        HuffmanArchiver(std::string file);

        HuffmanArchiver();

        ~HuffmanArchiver();

        void write_size(std::string file_in, std::ostream& out);

        friend std::istream& operator>>(std::istream &stream, HuffmanArchiver &archiver);

        friend std::ostream& operator<<(std::ostream &stream, HuffmanArchiver &archiver);

        void encode(std::string file_in, std::ostream& out);

        void decode(std::istream &in, std::string file_out);
    };
}