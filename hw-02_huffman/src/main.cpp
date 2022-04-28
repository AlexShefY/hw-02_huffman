#include <iostream>
#include <cstring>
#include "exceptions.hpp"
#include "main_functions.hpp"

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cout << "Wrong number of arguments";
        exit(1);
    }
    if (argv[1] != std::string_view("-c") && argv[1] != std::string_view("-u")) {
        std::cout << ("wrong flag " + std::string(argv[1]));
        exit(1);
    }
    if (argv[2] != std::string_view("-f")) {
        std::cout << ("wrong flag " + std::string(argv[2]));
        exit(1);
    }
    if (argv[4] != std::string_view("-o")) {
        std::cout << ("wrong flag " + std::string(argv[4]));
        exit(1);
    }
    try {
        if (argv[1] == std::string_view("-c")) {
            encode(argv[3], argv[5]);
        } else {
            decode(argv[3], argv[5]);
        }
    }
    catch (Exceptions::MyException &e) {
        std::cout << e.what();
        exit(1);
    }
    return 0;
}