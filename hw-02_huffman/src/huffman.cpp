#include <fstream>
#include "huffman.hpp"
#include "tree.hpp"
#include "exceptions.hpp"
#include <algorithm>

namespace huffman_compression {

    void HuffmanArchiver::read_tree(std::istream &stream) {
        local_tree = new Tree();
        stream >> *local_tree;
        tree_size = local_tree->byte_size;
        tree_size += sizeof(int);
    }

    void HuffmanArchiver::write_tree(std::ostream &stream) {
        stream << *local_tree;
        tree_size = local_tree->byte_size;
        tree_size += sizeof(int);
    }

    HuffmanArchiver::HuffmanArchiver() {
        local_tree = nullptr;
    }

    void HuffmanArchiver::build(std::string file) {
        std::ifstream stream(file);
        std::map<char, int> stat_symbols = map_from_text(stream, text_size);
        local_tree = new Tree(stat_symbols);
    }

    HuffmanArchiver::~HuffmanArchiver() {
        delete local_tree;
    }

    void HuffmanArchiver::process_byte(bool byte, std::ostream &stream) {
        bytes_size++;
        static int8_t int_bytes = 0;
        static size_t count_bytes = 0;
        count_bytes++;
        int_bytes = int_bytes * 2 + int8_t(byte);
        if (count_bytes == 8) {
            stream.write(reinterpret_cast<const char *>(&int_bytes), sizeof(int_bytes));
            if (stream.fail()) {
                throw Exceptions::MyException("Failed to write byte");
            }
            int_bytes = 0;
            count_bytes = 0;
        }
    }

    void HuffmanArchiver::write_size(std::string file_in, std::ostream& out) {
        std::ifstream in(file_in);
        if (!in) {
            throw Exceptions::MyException(("No such file " + file_in).c_str());
        }
        char t;
        in.read(&t, sizeof(char));
        if (in.fail() && !in.eof()) {
            throw Exceptions::MyException("Failed to read text");
        }
        std::map<char, std::vector<bool>> mp;
        local_tree->get_map(mp);
        int size = 0;
        while (!in.eof()) {
            size += mp[t].size();
            in.read(&t, sizeof(char));
            if (in.fail() && !in.eof()) {
                throw Exceptions::MyException("Failed to read text");
            }
        }
        out.write(reinterpret_cast<const char *>(&size), sizeof(size));
        if (out.fail()) {
            throw Exceptions::MyException("Failed to write size");
        }
    }

    std::map<char, int> HuffmanArchiver::map_from_text(std::istream &stream, int &size) {
        std::map<char, int> mp;
        char t;
        stream.read(&t, sizeof(char));
        if (stream.fail() && !stream.eof()) {
            throw Exceptions::MyException("Failed to read text");
        }
        while (!stream.eof()) {
            mp[t]++;
            size++;
            stream.read(&t, sizeof(char));
            if (stream.fail() && !stream.eof()) {
                throw Exceptions::MyException("Failed to read text");
            }
        }
        return mp;
    }

    void HuffmanArchiver::encode(std::string file_in, std::ostream& out) {
        std::ifstream in(file_in);
        if (!in) {
            throw Exceptions::MyException(("No such file " + file_in).c_str());
        }
        char t;
        in.read(&t, sizeof(char));
        if (in.fail() && !in.eof()) {
            throw Exceptions::MyException("Failed to read text");
        }
        std::map<char, std::vector<bool>> mp;
        local_tree->get_map(mp);
        while (!in.eof()) {
            for (auto byte : mp[t]) {
                process_byte(byte, out);
            }
            in.read(&t, sizeof(char));
            if (in.fail() && !in.eof()) {
                throw Exceptions::MyException("Failed to read text");
            }
        }
        size_t remainder = (8 - bytes_size % 8) % 8;
        while (remainder--) {
            process_byte(false, out);
        }
        bytes_size /= 8;
    }

    void HuffmanArchiver::decode(std::istream& in, std::string file_out) {
        std::ofstream out(file_out);
        if (!out) {
            throw Exceptions::MyException(("No such file " + file_out).c_str());
        }
        int size;
        in.read(reinterpret_cast<char *>(&size), sizeof(size));
        if (in.fail()) {
            throw Exceptions::MyException("Failed to read bytes");
        }
        uint8_t byte;
        int iter = (size + 7) / 8;
        std::vector <bool> ans;
        for (int j = 0; j < iter; j++) {
            in.read(reinterpret_cast<char *>(&byte), sizeof(byte));
            if (in.fail()) {
                throw Exceptions::MyException("Failed to read bytes");
            }
            bytes_size += sizeof(byte);
            std::vector <int> vec(8);
            int val = static_cast<int>(byte);
            for (size_t i = 0; i < 8; i++) {
                vec[i] = val % 2;
                val /= 2;
            }
            reverse(vec.begin(), vec.end());
            size_t i = 0;
            while (size > 0 && i < vec.size()) {
                bool flag = false;
                char cur = local_tree->move(vec[i], flag);
                if (flag) {
                    text_size++;
                    out.write(reinterpret_cast<char*>(&cur), sizeof(cur));
                    if (out.fail()) {
                        throw Exceptions::MyException("Failed to write text");
                    }
                }
                size--;
                i++;
            }
        }
    }

    HuffmanArchiver::HuffmanArchiver(const HuffmanArchiver &other) {
        local_tree = other.local_tree;
        bytes_size = other.bytes_size;
        text_size = other.text_size;
        tree_size = other.tree_size;
    }

    HuffmanArchiver &HuffmanArchiver::operator=(HuffmanArchiver other) {
        local_tree = std::exchange(other.local_tree, nullptr);
        bytes_size = std::exchange(other.bytes_size, 0);
        tree_size = std::exchange(other.tree_size, 0);
        text_size = std::exchange(other.text_size, 0);
        return *this;
    }
}