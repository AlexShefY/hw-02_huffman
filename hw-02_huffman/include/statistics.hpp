#pragma once
#include "tree.hpp"

namespace Statistics {
    class Statistics {
        std::priority_queue<std::pair<int, Trees::Node*>> counter;

    public:
        Statistics(const std::map <char, int> &mp);

        bool one_elem();

        Trees::Node* extract();

        void add(Trees::Node *c);

        Statistics(const Statistics& other);

        Statistics& operator=(const Statistics& other);

        ~Statistics();
    };
}
