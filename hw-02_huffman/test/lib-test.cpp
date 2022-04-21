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
        std::string file_in_name = "../test/sample_text.txt";
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
        std::string file_in_name = "../test/sample_big.txt";
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
        std::string file_in_name = "../test/sample_empty.txt";
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
        std::string file_in_name = "../test/sample_one.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        CHECK_EQ(process_file(file_in_name, binary_name, file_out_name), 0);
        std::ifstream file_in(file_in_name);
        std::ifstream file_out_in(file_out_name);
        CHECK_EQ(
                std::equal(std::istreambuf_iterator<char>(file_in), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(file_out_in)),
                true);
    }

    TEST_CASE("test tree") {
        std::map<char, int> mp_counter;
        for (int i = 0; i < 26; i++) {
            mp_counter['a' + i] = random() + 1;
        }
        Trees::Tree tree(mp_counter);
        std::map<char, std::vector<bool>> mp_bytes;
        tree.get_map(mp_bytes);
        for (int i = 0; i < 26; i++) {
            char symbol = 'a' + i;
            char ans = -1;
            bool flag = false;
            for (auto byte : mp_bytes[symbol]) {
                CHECK_EQ(ans, -1);
                ans = tree.move(byte, flag);
            }
            CHECK_EQ(symbol, ans);
            CHECK_EQ(flag, true);
        }
    }
}