#include "help_functions.hpp"


std::vector <bool> read_bytes(std::istream& stream, size_t &calc_size) {
    int size;
    stream.read(reinterpret_cast<char *>(&size), sizeof(size));
    uint8_t byte;
    int iter = (size + 7) / 8;
    std::vector <bool> ans;
    for (int j = 0; j < iter; j++) {
        stream.read(reinterpret_cast<char *>(&byte), sizeof(byte));
        calc_size += sizeof(byte);
        std::vector <int> vec(8);
        int val = static_cast<int>(byte);
        for (size_t i = 0; i < 8; i++) {
            vec[i] = val % 2;
            val /= 2;
        }
        reverse(vec.begin(), vec.end());
        size_t i = 0;
        while (size > 0 && i < vec.size()) {
            ans.push_back(vec[i]);
            size--;
            i++;
        }
    }
    return ans;
}
