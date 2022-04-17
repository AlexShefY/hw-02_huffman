#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "tree.hpp"

namespace Encode {
    class Encode {
    public:
        std::vector<char> symbols;
        std::map<char, int> stat_symbols;
        Trees::Tree* local_tree;
        size_t file_size = 0;
        size_t tree_size = 0;
        size_t code_size = 0;

        void build();

        friend std::istream& operator>>(std::istream &stream, Encode &encoder);

        friend std::ostream& operator<<(std::ostream &stream, Encode &encoder);

        ~Encode();
    };
}

namespace Decode {
    class Decode {
    public:

        size_t file_size = 0;
        size_t tree_size = 0;
        size_t code_size = 0;
        Trees::Tree* local_tree = new Trees::Tree();
        std::vector<char> symbols;

        friend std::istream& operator>>(std::istream &stream, Decode &decoder);

        friend std::ostream& operator<<(std::ostream &stream, Decode &decoder);

        ~Decode();
    };
}