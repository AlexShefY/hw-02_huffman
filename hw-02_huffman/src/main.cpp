#include <iostream>
#include <cstring>
#include <fstream>
#include "exceptions.hpp"
#include "huffman.hpp"
#include "help_functions.hpp"

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cout << "Wrong number of arguments";
        exit(1);
    }
    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-u") != 0) {
        std::cout << ("wrong flag " + std::string(argv[1]));
        exit(1);
    }
    if (strcmp(argv[2], "-f") != 0) {
        std::cout << ("wrong flag " + std::string(argv[2]));
        exit(1);
    }
    if (strcmp(argv[4], "-o") != 0) {
        std::cout << ("wrong flag " + std::string(argv[4]));
        exit(1);
    }
    if (strcmp(argv[1], "-c") == 0) {
        std::ifstream file_in(argv[3]);
        if (!file_in) {
            std::cout << "No such file " << argv[3];
            exit(1);
        }
        std::vector<char> text = read_text(file_in);
        HuffmanArchiver::HuffmanArchiver archiver(map_from_text(text));
        std::vector<bool> bytes = archiver.encode(text);
        std::ofstream file_out(argv[5]);
        if (!file_out) {
            std::cout << "No such file " << argv[5];
            exit(1);
        }
        file_out << archiver;
        size_t size_bytes = 0;
        write_bytes(file_out, bytes, size_bytes);
        std::cout << sizeof(char) * text.size() << "\n";
        std::cout << size_bytes << "\n";
        std::cout << archiver.tree_size << "\n";
    } else {
        std::ifstream file_in(argv[3]);
        if (!file_in) {
            std::cout << "No such file " << argv[3];
            exit(1);
        }
        HuffmanArchiver::HuffmanArchiver archiver;
        file_in >> archiver;
        size_t size_bytes = 0;
        std::vector<bool> bytes = read_bytes(file_in, size_bytes);
        std::vector<char> text = archiver.decode(bytes);
        std::ofstream file_out(argv[5]);
        if (!file_out) {
            std::cout << "No such file " << argv[5];
            exit(1);
        }
        write_text(file_out, text);
        std::cout << size_bytes << "\n";
        std::cout << sizeof(char) * text.size() << "\n";
        std::cout << archiver.tree_size << "\n";
    }
    return 0;
}