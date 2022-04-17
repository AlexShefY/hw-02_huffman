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

        void build();

        friend std::istream& operator>>(std::istream &stream, Encode &encoder);

        friend std::ostream& operator<<(std::ostream &stream, const Encode &encoder);

        ~Encode();
    };
}

namespace Decode {
    class Decode {
    public:
        Trees::Tree* local_tree = new Trees::Tree();
        std::vector<char> symbols;

        friend std::istream& operator>>(std::istream &stream, Decode &decoder);

        friend std::ostream& operator<<(std::ostream &stream, const Decode &decoder);

        ~Decode();
    };
}