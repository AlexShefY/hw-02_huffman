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