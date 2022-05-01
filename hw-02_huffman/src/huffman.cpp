#include <fstream>
#include "huffman.hpp"
#include "tree.hpp"
#include "exceptions.hpp"
#include <algorithm>

namespace huffman_compression {

    Statistics::Statistics() : tree_size(0), text_size(0), bytes_size(0) {
    }

    void process_byte(bool byte, std::ostream &stream, Statistics& statistics) {
        statistics.bytes_size++;
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

    int get_size(std::string file_in, const Tree& tree) {
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
        tree.get_map(mp);
        int bites_size = 0;
        while (!in.eof()) {
            bites_size += mp[t].size();
            in.read(&t, sizeof(char));
            if (in.fail() && !in.eof()) {
                throw Exceptions::MyException("Failed to read text");
            }
        }
        return bites_size;
    }

    std::map<char, int> map_from_text(std::istream &stream, Statistics &statistics) {
        std::map<char, int> mp;
        char t;
        stream.read(&t, sizeof(char));
        if (stream.fail() && !stream.eof()) {
            throw Exceptions::MyException("Failed to read text");
        }
        while (!stream.eof()) {
            mp[t]++;
            statistics.text_size++;
            stream.read(&t, sizeof(char));
            if (stream.fail() && !stream.eof()) {
                throw Exceptions::MyException("Failed to read text");
            }
        }
        return mp;
    }

    void encode(std::string file_in, std::ostream& out, const Tree& tree, Statistics& statistics) {
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
        tree.get_map(mp);
        while (!in.eof()) {
            for (auto byte : mp[t]) {
                process_byte(byte, out, statistics);
            }
            in.read(&t, sizeof(char));
            if (in.fail() && !in.eof()) {
                throw Exceptions::MyException("Failed to read text");
            }
        }
        size_t remainder = (8 - statistics.bytes_size % 8) % 8;
        while (remainder--) {
            process_byte(false, out, statistics);
        }
        statistics.bytes_size /= 8;
    }

    void decode(std::istream &in, std::string file_out, Tree& tree, Statistics& statistics) {
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
            statistics.bytes_size += sizeof(byte);
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
                char cur = tree.move(vec[i], flag);
                if (flag) {
                    statistics.text_size++;
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