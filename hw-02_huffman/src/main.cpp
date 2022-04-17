#include <iostream>
#include <cstring>
#include "exceptions.hpp"

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

        } else {

        }
    }
    catch (Exceptions::MyException& e) {
        std::cout << e.message;
    }
    return 0;
}