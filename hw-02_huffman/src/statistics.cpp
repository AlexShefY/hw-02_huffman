#include "statistics.hpp"

namespace Statistics {
    Statistics::Statistics(const std::map<char, int> &mp) {
        for (auto p: mp) {
            auto *node = new Trees::Node(p.first, p.second);
            counter.push({-node->count, node});
        }
    }

    Trees::Node* Statistics::extract() {
        Trees::Node *res = counter.top().second;
        counter.pop();
        return res;
    }

    void Statistics::add(Trees::Node *c) {
        counter.push({-c->count, c});
    }

    bool Statistics::one_elem() {
        return counter.size() == 1;
    }

    Statistics::Statistics(const Statistics &other) : counter(other.counter) {
    }

    Statistics& Statistics::operator=(const Statistics &other) {
        if (this != &other) {
            this->counter = other.counter;
        }
        return *this;
    }

    Statistics::~Statistics() {
        while (!counter.empty()) {
            counter.pop();
        }
    }
}
