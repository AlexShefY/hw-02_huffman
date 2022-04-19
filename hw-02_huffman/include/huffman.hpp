#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "tree.hpp"

namespace HuffmanArchiver {
    class HuffmanArchiver {
        Trees::Tree* local_tree;
    public:
        size_t tree_size = 0;

        HuffmanArchiver(const std::map <char, int> &stat_symbols);

        HuffmanArchiver();

        ~HuffmanArchiver();

        friend std::istream& operator>>(std::istream &stream, HuffmanArchiver &archiver);

        friend std::ostream& operator<<(std::ostream &stream, HuffmanArchiver &archiver);

        std::vector <bool> encode(std::vector <char> text);

        std::vector <char> decode(std::vector <bool> bytes);
    };
}

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

        std::vector<bool> encode();

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