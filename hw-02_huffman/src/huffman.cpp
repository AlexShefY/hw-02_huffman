
#include "huffman.hpp"
#include "tree.hpp"

namespace Encode {
    std::istream &operator>>(std::istream &stream, Encode &encoder) {
        char* t = new char;
        stream.read(t, sizeof(char));
        while (!stream.eof()) {
            encoder.stat_symbols[*t]++;
            encoder.symbols.push_back(*t);
            stream.read(t, sizeof(char));
        }
        delete t;
        encoder.build();
        return stream;
    }

    void Encode::Encode::build() {
        local_tree = new Trees::Tree(stat_symbols);
    }

    std::ostream &operator<<(std::ostream &stream, const Encode &encoder) {
        std::map<char, std::vector<bool>> mp;
        encoder.local_tree->get_map(mp);
        std::vector<bool> bytes;
        for (auto t : encoder.symbols) {
            for (auto e : mp[t]) {
                bytes.push_back(e);
            }
        }
        stream << *encoder.local_tree;
        int sz = bytes.size();
        while (bytes.size() % 8 != 0) {
            bytes.push_back(0);
        }
        stream.write(reinterpret_cast<const char *>(&sz), sizeof(sz));
        for (size_t i = 0; i < bytes.size(); i += 8) {
            uint8_t a = 0;
            for (int j = 0; j < 8; j++) {
                a = a * 2 + bytes[i + j];
            }
            stream.write(reinterpret_cast<const char *>(&a), sizeof(a));
        }
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
        int size;
        stream.read(reinterpret_cast<char *>(&size), sizeof(size));
        uint8_t byte;
        while (stream.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
            std::vector <int> vec(8);
            int val = static_cast<int>(byte);
            for (size_t i = 0; i < 8; i++) {
                vec[i] = val % 2;
                val /= 2;
            }
            reverse(vec.begin(), vec.end());
            size_t i = 0;
            while (size > 0 && i < vec.size()) {
                char cur = decoder.local_tree->move(vec[i]);
                if (cur != -1) {
                    decoder.symbols.push_back(cur);
                }
                size--;
                i++;
            }
        }
        return stream;
    }

    std::ostream& operator<<(std::ostream& stream, const Decode &decoder) {
        for (auto c : decoder.symbols) {
            stream.write(reinterpret_cast<const char *>(&c), sizeof(c));
        }
        return stream;
    }
}