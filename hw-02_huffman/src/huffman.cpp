#include <fstream>
#include "huffman.hpp"
#include "tree.hpp"
#include "help_functions.hpp"
#include "exceptions.hpp"
#include <algorithm>

namespace HuffmanArchiver {

    std::istream &operator>>(std::istream &stream, HuffmanArchiver &archiver) {
        archiver.local_tree = new Trees::Tree();
        stream >> *archiver.local_tree;
        archiver.tree_size = archiver.local_tree->byte_size;
        archiver.tree_size += sizeof(int);
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, HuffmanArchiver &archiver) {
        stream << *archiver.local_tree;
        archiver.tree_size = archiver.local_tree->byte_size;
        archiver.tree_size += sizeof(int);
        return stream;
    }

    HuffmanArchiver::HuffmanArchiver() {
        local_tree = nullptr;
    }

    void HuffmanArchiver::build(std::string file) {
        std::ifstream stream(file);
        std::map<char, int> stat_symbols = help_functions::map_from_text(stream, text_size);
        local_tree = new Trees::Tree(stat_symbols);
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
}