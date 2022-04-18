
#include<iostream>
#include <cassert>
#include "tree.hpp"

namespace Trees {

    Node::Node(char symbol, int count) : symbol(symbol), count(count) {
    }

    Tree::Tree() {
    }

    Node::~Node() {
        delete left;
        delete right;
    }

    int Node::operator<(const Node &other) const {
        return -(count - other.count);
    }

    Tree::~Tree() {
        delete root;
    }

    char Tree::move(int bit) {
        if (bit == 0) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
        if (cur->left != nullptr) {
            return -1;
        } else {
            char ans = cur->symbol;
            cur = root;
            return ans;
        }
    }

    Tree::Tree(std::map<char, int> mp) {
        if (mp.size() == 0) {
            return;
        }
        Statistics::Statistics stat = Statistics::Statistics(mp);
        if (stat.one_elem()) {
            Node* node1 = stat.extract();
            Node* node0 = new Node(-1, node1->count);
            node0->left = node1;
            root = node0;
            cur = root;
            return;
        }
        while (!stat.one_elem()) {
            Node *node1 = stat.extract();
            Node *node2 = stat.extract();
            Node *node0 = new Node(-1, node1->count + node2->count);
            node0->left = node1;
            node0->right = node2;
            stat.add(node0);
        }
        root = stat.extract();
        cur = root;
    }

    void Node::get_map(std::map<char, std::vector<bool>> &mp, std::vector<bool> &vec) const {
        if (left == nullptr && right == nullptr) {
            mp[symbol] = vec;
        }
        if (left != nullptr) {
            vec.push_back(0);
            left->get_map(mp, vec);
            vec.pop_back();
        }
        if (right != nullptr) {
            vec.push_back(1);
            right->get_map(mp, vec);
            vec.pop_back();
        }
    }

    void Tree::get_map(std::map<char, std::vector<bool>> &mp) const {
        std::vector<bool> vec;
        root->get_map(mp, vec);
    }

    void Node::add_nodes(char c, const std::vector<bool> &vec, size_t i) {
        if (i == vec.size()) {
            symbol = c;
            return;
        }
        if (vec[i] == 0) {
            if (left == nullptr) {
                left = new Node(-1, 0);
            }
            left->add_nodes(c, vec, i + 1);
        }
        else {
            if (right == nullptr) {
                right = new Node(-1, 0);
            }
            right->add_nodes(c, vec, i + 1);
        }
    }

    std::ostream& operator<<(std::ostream& stream, Tree& tree) {
        std::map<char, std::vector<bool>> mp;
        tree.get_map(mp);
        int sz = mp.size();
        stream.write(reinterpret_cast <const char*>(&sz), sizeof(sz));
        tree.byte_size += sizeof(sz);
        for (auto item : mp) {
            stream.write(reinterpret_cast<const char*> (&item.first), sizeof(item.first));
            tree.byte_size += sizeof(item.first);
            uint8_t sz1 =item.second.size();
            stream.write(reinterpret_cast<const char*> (&sz1), sizeof(sz1));
            tree.byte_size += sizeof(sz1);
            while (item.second.size() % 8 != 0) {
                item.second.push_back(0);
            }
            for (size_t i = 0; i < item.second.size(); i += 8) {
                uint8_t a = 0;
                for (size_t j = 0; j < 8; j++) {
                    a = a * 2 + item.second[j + i];
                }
                tree.byte_size += sizeof(a);
                stream.write(reinterpret_cast<const char *>(&a), sizeof(a));
            }
        }
        return stream;
    }

    void Tree::build(std::map<char, std::vector<bool>> &mp) {
        root = new Node(-1, 0);
        cur = root;
        for (auto p : mp) {
            root->add_nodes(p.first, p.second, 0);
        }
    }

    std::istream& operator>>(std::istream& stream, Tree& tree) {
        int sz;
        stream.read(reinterpret_cast<char*>(&sz), sizeof(sz));
        tree.byte_size += sizeof(sz);
        std::map<char, std::vector<bool>> mp;
        for (int i = 0; i < sz; i++) {
            char c = 0;
            stream.read(reinterpret_cast<char *>(&c), sizeof(c));
            tree.byte_size += sizeof(c);
            uint8_t sz1 = 0;
            stream.read(reinterpret_cast<char *>(&sz1), sizeof(sz1));
            tree.byte_size += sizeof(sz1);
            std::vector <bool> code;
            for (int j = 0; j < (sz1 + 7) / 8; j++) {
                uint8_t a = 0;
                stream.read(reinterpret_cast<char *>(&a), sizeof(a));
                tree.byte_size += sizeof(a);
                std::vector <bool> vec;
                int val = static_cast<int>(a);
                for (size_t k = 0; k < 8; k++) {
                    vec.push_back(static_cast<bool>(val % 2));
                    val /= 2;
                }
                reverse(vec.begin(), vec.end());
                size_t k = 0;
                while (sz1 > 0 && k < vec.size()) {
                    code.push_back(vec[k]);
                    k++;
                    sz1--;
                }
            }
            assert(sz1 == 0);
            mp[c] = code;
        }
        tree.root = nullptr;
        tree.build(mp);
        return stream;
    }
}
