#include <string>
#include <iostream>
#include "exceptions.hpp"
#include "main_functions.hpp"
#include "doctest.h"

namespace tests {

    int process_file(std::string file_in_name, std::string binary_name, std::string file_out_name) {
        try {
            encode(file_in_name, binary_name);
            decode(binary_name, file_out_name);
        }
        catch (Exceptions::MyException &e) {
            std::cout << e.message;
            return 1;
        }
        return 0;
    }

    TEST_CASE("small file") {
        std::string file_in_name = "../tests/sample1.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        CHECK_EQ(process_file(file_in_name, binary_name, file_out_name), 0);
        std::ifstream file_in(file_in_name);
        std::ifstream file_out_in(file_out_name);
        CHECK_EQ(
                std::equal(std::istreambuf_iterator<char>(file_in), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(file_out_in)),
                true);
    }

    TEST_CASE("big file") {
        std::string file_in_name = "../tests/sample_big.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        CHECK_EQ(process_file(file_in_name, binary_name, file_out_name), 0);
        std::ifstream file_in(file_in_name);
        std::ifstream file_out_in(file_out_name);
        CHECK_EQ(
                std::equal(std::istreambuf_iterator<char>(file_in), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(file_out_in)),
                true);
    }

    TEST_CASE("empty file") {
        std::string file_in_name = "../tests/sample_empty.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        CHECK_EQ(process_file(file_in_name, binary_name, file_out_name), 0);
        std::ifstream file_in(file_in_name);
        std::ifstream file_out_in(file_out_name);
        CHECK_EQ(
                std::equal(std::istreambuf_iterator<char>(file_in), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(file_out_in)),
                true);
    }

    TEST_CASE("one letter") {
        std::string file_in_name = "../tests/sample_one.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        CHECK_EQ(process_file(file_in_name, binary_name, file_out_name), 0);
        std::ifstream file_in(file_in_name);
        std::ifstream file_out_in(file_out_name);
        CHECK_EQ(
                std::equal(std::istreambuf_iterator<char>(file_in), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(file_out_in)),
                true);
    }
}