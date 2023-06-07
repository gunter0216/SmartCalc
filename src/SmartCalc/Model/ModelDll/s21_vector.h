#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include "s21_node.h"

namespace s21 {
class vector {
 public:
    typedef Node T;

    vector();
    explicit vector(size_t size);
    vector(const vector& other);
    ~vector();
    vector& operator=(const vector& other);
    vector& operator+=(const T& value) {
        push_back(value);
        return *this;
    }

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    bool empty() const;
    size_t size() const;

    void clear();
    void push_back(T count);
    void pop_back();

 private:
    T* _vector;
    size_t _size;
    size_t _capacity;
};

vector::vector() : _size(0), _capacity(0), _vector(nullptr) {}

vector::vector(size_t size) : _size(size), _capacity(size) {
    _vector = (T*)malloc(size * sizeof(T));
}

vector::vector(const vector& other) {
    if (&other != this) {
        _size = other._size;
        _capacity = other._capacity;
        _vector = (T*)malloc(_capacity * sizeof(T));
        for (size_t i = 0; i < _capacity; ++i) {
            _vector[i] = other._vector[i];
        }
    }
}

vector::~vector() {
    if (_vector != nullptr) {
        free(_vector);
    }
}

vector& vector::operator=(const vector& other) {
    if (_vector != nullptr) {
        free(_vector);
    }
    _size = other._size;
    _capacity = other._capacity;
    _vector = (T*)malloc(_capacity * sizeof(T));
    for (size_t i = 0; i < _size; ++i) {
        _vector[i] = other._vector[i];
    }
    return *this;
}

vector::T& vector::operator[](size_t pos) {
    return *(_vector + pos);
}

const vector::T& vector::operator[](size_t pos) const {
    return *(_vector + pos);
}

bool vector::empty() const {
    return 0 == size();
}

size_t vector::size() const {
    return _size;
}

void vector::clear() {
    if (_vector != nullptr) {
        _size = 0;
        _capacity = 0;
        free(_vector);
        _vector = nullptr;
    }
}

void vector::push_back(T count) {
    if (_capacity == 0) {
        _size = 1;
        _capacity = _size;
        _vector = (T*)malloc(_capacity * sizeof(T));
        _vector[0] = count;
    } else if (_size == _capacity) {
        vector temp(*this);
        _capacity *= 2;
        free(_vector);
        _vector = (T*)malloc(_capacity * sizeof(T));
        size_t i = 0;
        for (; i < _size; ++i) {
            _vector[i] = temp._vector[i];
        }
        _vector[_size] = count;
        ++_size;
    } else {
        _vector[_size] = count;
        ++_size;
    }
}

void vector::pop_back() {
    if (_size > 0)
        --_size;
}

}  // namespace s21

#endif  // S21_VECTOR_H_
