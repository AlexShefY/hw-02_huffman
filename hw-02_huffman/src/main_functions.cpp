#include "main_functions.hpp"

namespace main_functions {
    void encode(std::string file_in_name, std::string file_out_name, std::ostream &stream) {
        auto statistics = huffman_compression::Statistics();
        std::ifstream file_in(file_in_name);
        auto tree = huffman_compression::Tree(huffman_compression::map_from_text(file_in, statistics));
        std::ofstream file_out(file_out_name);
        if (!file_out) {
            std::cout << "No such file " << file_out_name;
            exit(1);
        }
        file_out << tree;
        statistics.tree_size = tree.byte_size;
        statistics.tree_size += sizeof (int);
        int bites_size = huffman_compression::get_size(file_in_name, tree);
        file_out.write(reinterpret_cast<const char *>(&bites_size), sizeof (int));
        huffman_compression::encode(file_in_name, file_out, tree, statistics);
        stream << statistics.text_size << "\n";
        stream << statistics.bytes_size << "\n";
        stream << statistics.tree_size << "\n";
        file_out.close();
    }

    void decode(std::string file_in_name, std::string file_out_name, std::ostream &stream) {
        auto statistics = huffman_compression::Statistics();
        std::ifstream file_in(file_in_name);
        if (!file_in) {
            std::cout << "No such file " << file_in_name;
            exit(1);
        }
        auto tree = huffman_compression::Tree();
        file_in >> tree;
        statistics.tree_size = tree.byte_size;
        statistics.tree_size += sizeof (int);
        decode(file_in, file_out_name, tree, statistics);
        stream << statistics.bytes_size << "\n";
        stream << statistics.text_size << "\n";
        stream << statistics.tree_size << "\n";
        file_in.close();
    }
}