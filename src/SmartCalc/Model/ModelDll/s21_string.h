#ifndef S21_STRING_H_
#define S21_STRING_H_

#include <stdlib.h>

namespace s21 {
class string {
 public:
    static const size_t npos = -1;

    string();
    explicit string(size_t size);
    string(const string& other);
    string(const char* other);
    ~string();
    string& operator=(const string& other);
    string& operator+=(const string& other);
    string& operator+=(char c);

    char& operator[](size_t pos);
    char operator[](size_t pos) const;

    bool empty() const;
    size_t size() const;

    void clear();
    void push_back(char count);
    char* get_array() const;
    size_t find(const string& other) const;
    size_t find(const char* other) const;
    double to_double() const;
    void replace(char x1, char x2);
    bool null_or_whitespace() const;

 private:
    char* _arr;
    size_t _size;
    size_t _capacity;

    size_t size(const char* c) const;
};

string::string() : _size(0), _capacity(0), _arr(nullptr) {}

string::string(size_t size) : _size(size), _capacity(size + 1) {
    _arr = (char*)malloc(_capacity * sizeof(char));
}

string::string(const string& other) {
    if (&other != this) {
        _size = other._size;
        _capacity = other._capacity;
        _arr = (char*)malloc(_capacity * sizeof(char));
        for (size_t i = 0; i < _capacity; ++i) {
            _arr[i] = other._arr[i];
        }
    }
}

string::string(const char* other) {
    if (other != nullptr) {
        _size = this->size(other);
        _capacity = _size + 1;
        _arr = (char*)malloc(_capacity * sizeof(char));
        for (size_t i = 0; i < _size; ++i) {
            _arr[i] = other[i];
        }
        _arr[_size] = '\0';
    }
}

string::~string() {
    if (_arr != nullptr) {
        free(_arr);
    }
}

string& string::operator=(const string& other) {
    if (_arr != nullptr) {
        free(_arr);
    }
    _size = other._size;
    _capacity = other._capacity;
    _arr = (char*)malloc(_capacity * sizeof(char));
    for (size_t i = 0; i < _size; ++i) {
        _arr[i] = other._arr[i];
    }
    return *this;
}

string& string::operator+=(const string& other) {
    for (size_t i = 0; i < other._size; ++i) {
        this->push_back(other[i]);
    }
    return *this;
}

string& string::operator+=(char c) {
    this->push_back(c);
    return *this;
}

char& string::operator[](size_t pos) {
    return *(_arr + pos);
}

char string::operator[](size_t pos) const {
    return *(_arr + pos);
}

bool string::empty() const {
    return 0 == size();
}

size_t string::size() const {
    return _size;
}

void string::clear() {
    if (_arr != nullptr) {
        _size = 0;
        _capacity = 0;
        free(_arr);
        _arr = nullptr;
    }
}

void string::push_back(char count) {
    if (_capacity == 0) {
        _size = 1;
        _capacity = 2;
        _arr = (char*)malloc(_capacity * sizeof(char));
        _arr[0] = count;
        _arr[1] = '\0';
    } else if (_size == _capacity - 1) {
        string temp(*this);
        _capacity *= 2;
        free(_arr);
        _arr = (char*)malloc(_capacity * sizeof(char));
        size_t i = 0;
        for (; i < _size; ++i) {
            _arr[i] = temp._arr[i];
        }
        _arr[_size] = count;
        _arr[_size + 1] = '\0';
        ++_size;
    } else {
        _arr[_size] = count;
        _arr[_size + 1] = '\0';
        ++_size;
    }
}

char* string::get_array() const {
    return _arr;
}

size_t string::find(const string& other) const {
    for (size_t i = 0; i < _size - other._size + 1; ++i) {
        size_t j = 0;
        for (; j < other._size; ++j) {
            if (_arr[i + j] != other._arr[j]) {
                break;
            }
        }
        if (j == other._size) {
            return i;
        }
    }
    return npos;
}

size_t string::find(const char* other) const {
    size_t size = this->size(other);
    for (size_t i = 0; i < _size - size + 1; ++i) {
        size_t j = 0;
        for (; j < size; ++j) {
            if (_arr[i + j] != other[j]) {
                break;
            }
        }
        if (j == size) {
            return i;
        }
    }
    return npos;
}

double string::to_double() const {
    string temp(*this);
    temp.replace(',', '.');
    return strtod(temp._arr, NULL);
}

void string::replace(char x1, char x2) {
    for (size_t i = 0; i < _size; ++i) {
        if (_arr[i] == x1) {
            _arr[i] = x2;
        }
    }
}

size_t string::size(const char* c) const {
    size_t size = 0;
    while (c[size] != '\n' && c[size] != '\0') {
        ++size;
    }
    return size;
}

bool string::null_or_whitespace() const {
    if (_size > 0) {
        for (size_t i = 0; i < _size; ++i) {
            if (_arr[i] != ' ') {
                return false;
            }       
        }
    }
    return true;
}
}  // namespace s21

#endif  // S21_STRING_H_
