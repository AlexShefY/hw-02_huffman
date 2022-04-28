#include "tree.hpp"
#include "help_functions.hpp"
#include "exceptions.hpp"

namespace huffman_compression {

    Tree::Node::Node(char symbol, int count) : symbol(symbol), count(count) {
    }

    Tree::Tree() {
    }

    Tree::Node::~Node() {
        delete left;
        delete right;
    }

    Tree::~Tree() {
        delete root;
    }

    char Tree::move(int bit, bool &flag) {
        if (bit == 0) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
        if (cur->left != nullptr) {
            flag = false;
            return -1;
        } else {
            flag = true;
            char ans = cur->symbol;
            cur = root;
            return ans;
        }
    }

    Tree::Tree(const std::map<char, int> &mp) {
        if (mp.size() == 0) {
            return;
        }
        std::priority_queue<std::pair<int, Node*>> counter;
        for (auto p: mp) {
            auto *node = new Node(p.first, p.second);
            counter.push({-node->count, node});
        }
        if (counter.size() == 1) {
            Node* node1 = counter.top().second;
            counter.pop();
            Node* node0 = new Node(-1, node1->count);
            node0->left = node1;
            root = node0;
            cur = root;
            return;
        }
        while (counter.size() != 1) {
            Node *node1 = counter.top().second;
            counter.pop();
            Node *node2 = counter.top().second;
            counter.pop();
            Node *node0 = new Node(-1, node1->count + node2->count);
            node0->left = node1;
            node0->right = node2;
            counter.push({-node0->count, node0});
        }
        root = counter.top().second;
        counter.pop();
        cur = root;
    }

    void Tree::Node::get_map(std::map<char, std::vector<bool>> &mp, std::vector<bool> &vec) const {
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
        if (root == nullptr) {
            return;
        }
        std::vector<bool> vec;
        root->get_map(mp, vec);
    }

    void Tree::Node::add_nodes(char c, const std::vector<bool> &vec, size_t i) {
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
        if (stream.fail()) {
            throw Exceptions::MyException("fail to write tree");
        }
        tree.byte_size += sizeof(sz);
        for (auto item : mp) {
            stream.write(reinterpret_cast<const char*> (&item.first), sizeof(item.first));
            if (stream.fail()) {
                throw Exceptions::MyException("fail to write tree");
            }
            tree.byte_size += sizeof(item.first);
            tree.byte_size += sizeof(int);
            io_helpers::write_bytes(stream, item.second, tree.byte_size);
        }
        return stream;
    }

    void Tree::build(std::map<char, std::vector<bool>> &mp) {
        if (mp.size() == 0) {
            return;
        }
        root = new Node(-1, 0);
        cur = root;
        for (auto p : mp) {
            root->add_nodes(p.first, p.second, 0);
        }
    }

    std::istream& operator>>(std::istream& stream, Tree& tree) {
        int sz;
        stream.read(reinterpret_cast<char*>(&sz), sizeof(sz));
        if (stream.fail()) {
            throw Exceptions::MyException("fail to read tree");
        }
        tree.byte_size += sizeof(int);
        std::map<char, std::vector<bool>> mp;
        for (int i = 0; i < sz; i++) {
            char c = 0;
            stream.read(reinterpret_cast<char *>(&c), sizeof(c));
            if (stream.fail()) {
                throw Exceptions::MyException("fail to read tree");
            }
            tree.byte_size += sizeof(c);
            tree.byte_size += sizeof(int);
            mp[c] = io_helpers::read_bytes(stream, tree.byte_size);
        }
        tree.build(mp);
        return stream;
    }
}
