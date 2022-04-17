cmake_minimum_required(VERSION 3.16)

project(hw-02_huffman CXX)

add_executable(hw-02_huffman src/main.cpp test/test.cpp src/exceptions.cpp)

target_compile_features(hw-02_huffman PUBLIC cxx_std_20)

include_directories(include)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
