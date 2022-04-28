cmake_minimum_required(VERSION 3.16)

project(hw-02_huffman CXX)

add_executable(hw-02_huffman src/main.cpp src/exceptions.cpp src/huffman.cpp src/tree.cpp src/help_functions.cpp include/main_functions.hpp src/main_functions.cpp)

add_executable(hw-02_huffman_test test/test.cpp test/lib-test.cpp src/exceptions.cpp src/huffman.cpp src/tree.cpp src/help_functions.cpp src/main_functions.cpp)

target_compile_features(hw-02_huffman PUBLIC cxx_std_20)

target_compile_features(hw-02_huffman_test PUBLIC cxx_std_20)

include_directories(include)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
