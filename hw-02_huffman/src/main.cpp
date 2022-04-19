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
        std::vector<char> text = read_text(file_in);
        HuffmanArchiver::HuffmanArchiver archiver(map_from_text(text));
        std::vector<bool> bytes = archiver.encode(text);
        std::ofstream file_out(argv[5]);
        file_out << archiver;
        size_t size_bytes = 0;
        write_bytes(file_out, bytes, size_bytes);
        std::cout << sizeof(char) * text.size() << "\n";
        std::cout << size_bytes << "\n";
        std::cout << archiver.tree_size << "\n";
        /*
        Encode::Encode encoder;
        std::ifstream file_in(argv[3]);
        file_in >> encoder;
        encoder.build();
        std::ofstream file_out(argv[5]);
        file_out << encoder;
        std::cout << encoder.file_size << "\n";
        std::cout << encoder.code_size << "\n";
        std::cout << encoder.tree_size << "\n";*/
    } else {
        std::ifstream file_in(argv[3]);
        HuffmanArchiver::HuffmanArchiver archiver;
        file_in >> archiver;
        size_t size_bytes = 0;
        std::vector<bool> bytes = read_bytes(file_in, size_bytes);
        std::vector<char> text = archiver.decode(bytes);
        std::ofstream file_out(argv[5]);
        write_text(file_out, text);
        std::cout << size_bytes << "\n";
        std::cout << sizeof(char) * text.size() << "\n";
        std::cout << archiver.tree_size << "\n";
        /*
        Decode::Decode decoder;
        std::ifstream file_in(argv[3]);
        file_in >> decoder;
        std::ofstream file_out(argv[5]);
        file_out << decoder;
        std::cout << decoder.code_size << "\n";
        std::cout << decoder.file_size << "\n";
        std::cout << decoder.tree_size << "\n";*/
    }
    return 0;
}