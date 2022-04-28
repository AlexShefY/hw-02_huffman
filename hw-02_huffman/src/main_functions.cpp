#include "main_functions.hpp"

void encode(std::string file_in_name, std::string file_out_name, std::ostream& stream) {
    HuffmanArchiver::HuffmanArchiver archiver;
    archiver.build(file_in_name);
    std::ofstream file_out(file_out_name);
    if (!file_out) {
        std::cout << "No such file " << file_out_name;
        exit(1);
    }
    file_out << archiver;
    archiver.write_size(file_in_name, file_out);
    archiver.encode(file_in_name, file_out);
    stream << archiver.text_size << "\n";
    stream << archiver.bytes_size << "\n";
    stream << archiver.tree_size << "\n";
    file_out.close();
}

void decode(std::string file_in_name, std::string file_out_name,  std::ostream& stream) {
    std::ifstream file_in(file_in_name);
    if (!file_in) {
        std::cout << "No such file " << file_in_name;
        exit(1);
    }
    HuffmanArchiver::HuffmanArchiver archiver;
    file_in >> archiver;
    archiver.decode(file_in, file_out_name);
    stream << archiver.bytes_size << "\n";
    stream << archiver.text_size << "\n";
    stream << archiver.tree_size << "\n";
    file_in.close();
}