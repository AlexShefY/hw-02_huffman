#include <string>
#include <iostream>
#include "main_functions.hpp"
#include "doctest.h"

namespace tests {

    void process_file(std::string file_in_name, std::string binary_name, std::string file_out_name) {
        encode(file_in_name, binary_name);
        decode(binary_name, file_out_name);
    }

    bool file_equality(std::string file_in_name, std::string file_out_name) {
        std::ifstream file_in(file_in_name);
        std::ifstream file_out_in(file_out_name);
        return std::equal(std::istreambuf_iterator<char>(file_in),
                std::istreambuf_iterator<char>(),
                std::istreambuf_iterator<char>(file_out_in));
    }

    TEST_CASE("small file") {
        std::string file_in_name = "../test/sample_text.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        process_file(file_in_name, binary_name, file_out_name);
        CHECK(file_equality(file_in_name, file_out_name));
    }

    TEST_CASE("big file") {
        std::string file_in_name = "../test/sample_big.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        process_file(file_in_name, binary_name, file_out_name);
        CHECK(file_equality(file_in_name, file_out_name));
    }

    TEST_CASE("empty file") {
        std::string file_in_name = "../test/sample_empty.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        process_file(file_in_name, binary_name, file_out_name);
        CHECK(file_equality(file_in_name, file_out_name));
    }

    TEST_CASE("one letter") {
        std::string file_in_name = "../test/sample_one.txt";
        std::string binary_name = "output";
        std::string file_out_name = "my_txt.txt";
        process_file(file_in_name, binary_name, file_out_name);
        CHECK(file_equality(file_in_name, file_out_name));
    }

    void test_tree(Trees::Tree &tree) {
        std::map<char, std::vector<bool>> mp_bytes;
        tree.get_map(mp_bytes);
        for (int i = 0; i < 26; i++) {
            char symbol = 'a' + i;
            char ans = -1;
            bool flag = false;
            for (auto byte : mp_bytes[symbol]) {
                CHECK(!flag);
                ans = tree.move(byte, flag);
            }
            CHECK_EQ(symbol, ans);
            CHECK(flag);
        }
    }

    TEST_CASE("test tree powers") {
        std::map<char, int> mp_counter;
        for (int i = 0; i < 26; i++) {
            mp_counter['a' + i] = (1 << i);
        }
        Trees::Tree tree(mp_counter);
        test_tree(tree);
    }

    TEST_CASE("test tree ones") {
        std::map<char, int> mp_counter;
        for (int i = 0; i < 26; i++) {
            mp_counter['a' + i] = 1;
        }
        Trees::Tree tree(mp_counter);
        test_tree(tree);
    }

    TEST_CASE("tree build") {
        std::map<char, int> mp_counter;
        for (int i = 0; i < 26; i++) {
            mp_counter['a' + i] = 1;
        }
        Trees::Tree tree(mp_counter);
        Trees::Tree tree_build;
        std::map<char, std::vector<bool> > codes;
        tree.get_map(codes);
        tree_build.build(codes);
        test_tree(tree_build);
    }

    TEST_CASE("tree read write") {
        std::map<char, int> mp_counter;
        for (int i = 0; i < 26; i++) {
            mp_counter['a' + i] = i + 1;
        }
        Trees::Tree tree(mp_counter);
        std::map<char, std::vector<bool> > map_bytes;
        tree.get_map(map_bytes);
        std::ofstream file_out("out");
        file_out << tree;
        file_out.close();
        std::ifstream file_in("out");
        Trees::Tree tree_new;
        file_in >> tree_new;
        file_in.close();
        std::map<char, std::vector<bool> > map_bytes_new;
        tree_new.get_map(map_bytes_new);
        CHECK_EQ(map_bytes, map_bytes_new);
    }
}