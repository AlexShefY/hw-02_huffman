#pragma once

#include <queue>
#include <map>

namespace Trees {
    class Node {
    public:
        Node* right = nullptr;
        Node* left = nullptr;
        char symbol;
        int count;

        Node(char symbol, int count);
        int operator<(const Node& other) const;
        ~Node();

        void add_nodes(char c, const std::vector<bool>& vec, size_t i);
        void get_map(std::map<char, std::vector <bool>>& mp, std::vector <bool>& vec) const;
    };

    class Tree {
        Node* root;
        Node* cur;

    public:
        void get_map(std::map<char, std::vector<bool>> &mp) const;
        void build(std::map<char, std::vector<bool>> &mp);
        Tree(std::map<char, int> symbols_stat);
        Tree();
        friend std::ostream& operator<<(std::ostream& stream, const Tree& tree);
        friend std::istream& operator>>(std::istream& stream, Tree& tree);
        char move(int bit);

        ~Tree();
    };
}

namespace Statistics {
    class Statistics {
        std::priority_queue<std::pair<int, Trees::Node*>> counter;

    public:
        Statistics(std::map <char, int> mp);

        bool one_elem();

        Trees::Node* extract();

        void add(Trees::Node *c);

        Statistics(const Statistics& other);

        Statistics& operator=(const Statistics& other);

        ~Statistics();
    };
}
