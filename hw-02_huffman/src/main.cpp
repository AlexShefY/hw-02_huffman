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
    try {
        if (strcmp(argv[1], "-c") == 0) {
            HuffmanArchiver::HuffmanArchiver archiver(argv[3]);
            std::ofstream file_out(argv[5]);
            if (!file_out) {
                std::cout << "No such file " << argv[5];
                exit(1);
            }
            file_out << archiver;
            archiver.write_size(argv[3], file_out);
            archiver.encode(argv[3], file_out);
            std::cout << archiver.text_size << "\n";
            std::cout << archiver.bytes_size << "\n";
            std::cout << archiver.tree_size << "\n";
            file_out.close();
        } else {
            std::ifstream file_in(argv[3]);
            if (!file_in) {
                std::cout << "No such file " << argv[3];
                exit(1);
            }
            HuffmanArchiver::HuffmanArchiver archiver;
            file_in >> archiver;
            archiver.decode(file_in, argv[5]);
            std::cout << archiver.bytes_size << "\n";
            std::cout << archiver.text_size << "\n";
            std::cout << archiver.tree_size << "\n";
            file_in.close();
        }
    }
    catch (Exceptions::MyException &e) {
        std::cout << e.message;
    }
    return 0;
}