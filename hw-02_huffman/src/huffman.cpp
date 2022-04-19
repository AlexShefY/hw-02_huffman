#include "huffman.hpp"
#include "tree.hpp"

namespace HuffmanArchiver {

    std::istream &operator>>(std::istream &stream, HuffmanArchiver &archiver) {
        archiver.local_tree = new Trees::Tree();
        stream >> *archiver.local_tree;
        archiver.tree_size = archiver.local_tree->byte_size;
        archiver.tree_size += sizeof(int);
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, HuffmanArchiver &archiver) {
        stream << *archiver.local_tree;
        archiver.tree_size = archiver.local_tree->byte_size;
        archiver.tree_size += sizeof(int);
        return stream;
    }

    HuffmanArchiver::HuffmanArchiver() {
    }

    HuffmanArchiver::HuffmanArchiver(const std::map<char, int> &stat_symbols) {
        local_tree = new Trees::Tree(stat_symbols);
    }

    HuffmanArchiver::~HuffmanArchiver() {
        delete local_tree;
    }

    std::vector<bool> HuffmanArchiver::encode(std::vector<char> text) {
        std::map<char, std::vector<bool>> mp;
        local_tree->get_map(mp);
        std::vector<bool> bytes;
        for (auto t : text) {
            for (auto e : mp[t]) {
                bytes.push_back(e);
            }
        }
        return bytes;
    }

    std::vector<char> HuffmanArchiver::decode(std::vector<bool> bytes) {
        std::vector<char> ans;
        for (auto byte : bytes) {
            bool flag = false;
            char cur = local_tree->move(byte, flag);
            if (flag) {
                ans.push_back(cur);
            }
        }
        return ans;
    }
}