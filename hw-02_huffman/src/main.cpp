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
    std::string file_in_name, file_out_name;
    if (argv[2] == std::string_view("-f") && argv[4] == std::string_view("-o")) {
        file_in_name = argv[3];
        file_out_name = argv[5];
    }
    else if (argv[2] == std::string_view("-o") && argv[4] == std::string_view("-f")) {
        file_in_name = argv[5];
        file_out_name = argv[3];
    }
    else {
        std::cout << ("wrong flags " + std::string(argv[2]) + " " + std::string(argv[4]));
        exit(1);
    }
    try {
        if (argv[1] == std::string_view("-c")) {
            encode(file_in_name, file_out_name, std::cout);
        } else {
            decode(file_in_name, file_out_name, std::cout);
        }
    }
    catch (Exceptions::MyException &e) {
        std::cout << e.what();
        exit(1);
    }
    return 0;
}