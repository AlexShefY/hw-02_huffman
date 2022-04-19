#include "huffman.hpp"
#include "tree.hpp"
#include "help_functions.hpp"

namespace Encode {
    std::istream &operator>>(std::istream &stream, Encode &encoder) {
        char t;
        stream.read(&t, sizeof(char));
        while (!stream.eof()) {
            encoder.file_size += sizeof(char);
            encoder.stat_symbols[t]++;
            encoder.symbols.push_back(t);
            stream.read(&t, sizeof(char));
        }
        encoder.build();
        return stream;
    }

    void Encode::Encode::build() {
        local_tree = new Trees::Tree(stat_symbols);
    }

    std::ostream &operator<<(std::ostream &stream, Encode &encoder) {
        stream << *encoder.local_tree;
        encoder.tree_size = encoder.local_tree->byte_size;
        std::map<char, std::vector<bool>> mp;
        encoder.local_tree->get_map(mp);
        std::vector<bool> bytes;
        for (auto t : encoder.symbols) {
            for (auto e : mp[t]) {
                bytes.push_back(e);
            }
        }
        write_bytes(stream, bytes, encoder.code_size);
        encoder.tree_size += sizeof(int);
        return stream;
    }

    Encode::~Encode() {
        symbols.clear();
        stat_symbols.clear();
        delete local_tree;
    }
}

namespace Decode {

    Decode::~Decode() {
        symbols.clear();
        delete local_tree;
    }

    std::istream& operator>>(std::istream& stream, Decode &decoder) {
        stream >> *decoder.local_tree;
        decoder.tree_size = decoder.local_tree->byte_size;
        decoder.tree_size += sizeof(int);
        std::vector <bool> bytes = read_bytes(stream, decoder.code_size);
        for (auto byte : bytes) {
            bool flag = false;
            char cur = decoder.local_tree->move(byte, flag);
            if (flag) {
                decoder.symbols.push_back(cur);
            }
        }
        return stream;
    }

    std::ostream& operator<<(std::ostream& stream, Decode &decoder) {
        for (auto c : decoder.symbols) {
            stream.write(reinterpret_cast<const char *>(&c), sizeof(c));
            decoder.file_size += sizeof(c);
        }
        return stream;
    }
}