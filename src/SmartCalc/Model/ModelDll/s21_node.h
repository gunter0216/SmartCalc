#ifndef S21_NODE_H_
#define S21_NODE_H_

namespace s21 {
struct Node {
    Node() {
        first = 0.0;
        second = 0;
    }

    Node(double first, int second) {
        this->first = first;
        this->second = second;
    }
    double first;
    int second;

    bool operator==(Node const& other) {
        return other.first == this->first &&
               other.second == this->second;
    }

    bool operator!=(Node const& other) {
        return !(*this == other);
    }
};
}  // namespace s21

#endif  // S21_NODE_H_
