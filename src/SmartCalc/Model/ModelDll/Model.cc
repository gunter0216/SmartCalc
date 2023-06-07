#include "Model.h"

// меняет все х на переданное число
void s21::from_x_to_number_in_vector(s21::vector &vector, const double &x) {
    int size = vector.size();
    for (int i = 0; i < size; ++i)
        if (vector[i].second == Type::x) {
            vector[i].second = Type::number;
            vector[i].first = x;
        }
}

// удаляет повторяющие унарные операторы
void s21::delete_recurring_unary_operation(s21::vector &vector) {
    for (size_t i = 1; i < vector.size(); ++i) {
        if (vector[i - 1] == vector[i] && (vector[i].second == Type::uminus)) {
            vector[i - 1].second = Type::evoid;
            vector[i].second = Type::evoid;
        }
    }
}

// определяет приоритет
int s21::define_priority(int x) {
    int temp = 6;
    if (x == Type::cos || x == Type::sin || x == Type::atan || x == Type::tan ||
        x == Type::acos || x == Type::asin || x == Type::sqrt || x == Type::ln ||
        x == Type::log)
        temp = 1;
    else if (x == Type::uminus || x == Type::uplus)
        temp = 2;
    else if (x == Type::pow)
        temp = 3;
    else if (x == Type::mul || x == Type::div || x == Type::mod)
        temp = 4;
    else if (x == Type::plus || x == Type::minus)
        temp = 5;
    return temp;
}

size_t find(const s21::string &str, const char *other) {
    size_t other_size = 0;
    while (other[other_size] != '\n' && other[other_size] != '\0') {
        ++other_size;
    }
    if (str.size() >= other_size) {
        for (size_t i = 0; i < str.size() - other_size + 1; ++i) {
            size_t j = 0;
            for (; j < other_size; ++j) {
                if (str[i + j] != other[j]) {
                    break;
                }
            }
            if (j == other_size) {
                return i;
            }
        }
    }
    return -1;
}

// преобразует из строки в номер тригонометрической операции
int s21::define_trigonometry(const s21::string &str) {
    int temp = -1;
    int type[] = {
        Type::mod,
        Type::cos,
        Type::sin,
        Type::tan,
        Type::acos,
        Type::asin,
        Type::atan,
        Type::sqrt,
        Type::ln,
        Type::log,
    };
    const char strings[][10] = {
        "mod",
        "cos",
        "sin",
        "tan",
        "acos",
        "asin",
        "atan",
        "sqrt",
        "ln",
        "log",
    };
    for (int i = 0; i < 10; ++i) {
        if (find(str, strings[i]) != s21::string::npos) {
            temp = type[i];
        }
    }
    return temp;
}

// является ли символ одиночным(+-*/())
int s21::define_special_symbol(char x) {
    char symbols[] = "+-*/^()";
    int temp = -1;
    for (int j = 0; j < 7; j++) {
        if (symbols[j] == x) {
            if (symbols[j] == '+')
                temp = Type::plus;
            else if (symbols[j] == '-')
                temp = Type::minus;
            else if (symbols[j] == '*')
                temp = Type::mul;
            else if (symbols[j] == '/')
                temp = Type::div;
            else if (symbols[j] == '^')
                temp = Type::pow;
            else if (symbols[j] == '(')
                temp = Type::start;
            else if (symbols[j] == ')')
                temp = Type::end;
        }
    }
    return temp;
}

// является ли символ числом 0-9
bool s21::is_number(char x) {
    return (x >= '0' && x <= '9');
}

// является ли символ оператором(+-), числом(0-9) или частью строки(cos, sin)
int s21::define_category(char x) {
    char symbols[] = "+-*/^()";
    int result = -1;
    for (int j = 0; j < 8; ++j)
        if (x == symbols[j])
            result = Category::symbol;
    if (is_number(x) || x == '.' || x == ',' || x == 'x' || x == 'e')
        result = Category::number;
    else if (x >= 'a' && x <= 'z')
        result = Category::string;
    return result;
}

// выполняет операцию + - sin cos...
void s21::complete_operation(double &x1, double &x2, const int &operation) {
    if (operation == Type::plus) {
        x1 = x1 + x2;
    } else if (operation == Type::minus) {
        x1 = x1 - x2;
    } else if (operation == Type::uminus) {
        x2 = -x2;
    } else if (operation == Type::mul) {
        x1 = x1 * x2;
    } else if (operation == Type::div) {
        x1 = x1 / x2;
    } else if (operation == Type::pow) {
        x1 = pow(x1, x2);
    } else if (operation == Type::mod) {
        x1 = fmod(x1, x2);
    } else if (operation == Type::sin) {
        x2 = sin(x2 * M_PI / 180);
    } else if (operation == Type::cos) {
        x2 = cos(x2 * M_PI / 180);
    } else if (operation == Type::acos) {
        x2 = acos(x2) * 180 / M_PI;
    } else if (operation == Type::asin) {
        x2 = asin(x2) * 180 / M_PI;
    } else if (operation == Type::tan) {
        x2 = tan(x2 * M_PI / 180);
    } else if (operation == Type::atan) {
        x2 = atan(x2) / M_PI * 180;
    } else if (operation == Type::sqrt) {
        x2 = sqrt(x2);
    } else if (operation == Type::ln) {
        x2 = log(x2);
    } else if (operation == Type::log) {
        x2 = log10(x2);
    } else if (operation != Type::uplus) {
        model.error = true;
    }
}

bool s21::is_number(const s21::Node &item) {
    bool result = false;
    if (item.second == Type::number ||
        item.second == Type::x) {
        result = true;
    }
    return result;
}

bool s21::is_unary(const s21::Node &item) {
    bool result = false;
    if (item.second == Type::uminus ||
        item.second == Type::uplus) {
        result = true;
    }
    return result;
}

bool s21::is_trigonometry(const s21::Node &item) {
    bool result = false;
    if (item.second == Type::sin ||
        item.second == Type::asin ||
        item.second == Type::cos ||
        item.second == Type::acos ||
        item.second == Type::tan ||
        item.second == Type::atan ||
        item.second == Type::sqrt ||
        item.second == Type::log ||
        item.second == Type::ln) {
        result = true;
    }
    return result;
}

bool s21::is_special_operator(const s21::Node &item) {
    bool result = false;
    if (item.second == Type::minus ||
        item.second == Type::plus ||
        item.second == Type::mul ||
        item.second == Type::div ||
        item.second == Type::mod ||
        item.second == Type::pow) {
        result = true;
    }
    return result;
}

// добавляет в вектор элемент, преобразованный из строки, и проверяет его валидность
void s21::add_element(s21::vector &vector, s21::string &str) {
    if (str.null_or_whitespace() == false) {
        s21::Node node{0, Type::evoid};
        createElement(vector, str, node);
        if (node.second != Type::evoid)
            vector.push_back(node);
        else
            model.error = true;
    }
}

// высчитывает унарные операторы в начале
void s21::calc_unary_in_start_vector(s21::vector &vector) {
    int count_uminus_in_start = 0;
    int count_uplus_in_start = 0;
    size_t size = vector.size();
    size_t i = 0;
    for (; i < size && is_unary(vector[i]); ++i) {
        if (vector[i].second == Type::uminus)
            ++count_uminus_in_start;
        else if (vector[i].second == Type::uplus)
            ++count_uplus_in_start;
    }
    if (i < size && is_number(vector[i])) {
        if (count_uminus_in_start % 2 == 1)
            vector[0].first = -vector[0].first;
    } else {
        model.error = true;
    }
}

// добавляет count закрывающих скобок
void s21::push_close_braket_in_vector(s21::vector &vector, const int &count) {
    for (int i = 0; i < count; ++i)
        vector.push_back(s21::Node(0, Type::end));
}

// возвращает количество открывающих и закрывающих скобок
std::pair<int, int> s21::count_brakets_in_vector(const s21::vector &vector) {
    std::pair<int, int> result(0, 0);
    size_t size = vector.size();
    for (size_t i = 0; i < size; ++i) {
        if (vector[i].second == Type::start)
            ++result.first;
        else if (vector[i].second == Type::end)
            ++result.second;
    }
    return result;
}

void s21::correct_count_brakets_in_vector(s21::vector &vector) {
    auto count_brakets = count_brakets_in_vector(vector);
    if (count_brakets.first >= count_brakets.second)
        push_close_braket_in_vector(vector, count_brakets.first - count_brakets.second);
    else
        model.error = true;
}

// проверяется плавильность записанного обычного числа или экспоненциального
bool s21::is_correct_string_for_convert_to_number(const s21::string &str) {
    bool result = true;
    int count_points = 0;
    int count_e = 0;
    int count_symbols = 0;
    size_t size = str.size();
    for (size_t i = 0; i < size && result; ++i) {
        if (i == 0 && !is_number(str[i])) {
            result = false;
        } else if (i > 0) {
            if (str[i] == '+' || str[i] == '-') {
                if (str[i - 1] != 'e')
                    result = false;
                else
                    ++count_symbols;
            } else if (str[i] == 'e') {
                if (!is_number(str[i - 1]))
                    result = false;
                else
                    ++count_e;
            } else if (str[i] == '.' || str[i] == ',') {
                ++count_points;
            }
        }
    }
    if (result == true && (count_e > 1 ||
                           count_points > 1 ||
                           count_symbols > 1 ||
                           !is_number(str[str.size() - 1]))) {
        result = false;
    }
    return result;
}

double to_double(const s21::string &str) {
    s21::string temp(str);
    temp.replace(',', '.');
    return strtod(temp.get_array(), NULL);
}

void s21::createElement(s21::vector &vector, s21::string &str, s21::Node &stack) {
    int category = define_category(str[0]);
    if (category == Category::number) {
        if (str[0] == 'x') {
            stack = s21::Node(0, Type::x);
        } else {
            if (is_correct_string_for_convert_to_number(str)) {
                stack = s21::Node{to_double(str), 0};
            } else {
                model.error = true;
            }
        }
    } else if (category == Category::symbol) {
        int x2 = define_special_symbol(str[0]);
        if ((x2 == Type::minus || x2 == Type::plus) &&
            (vector.size() == 0 ||
             is_special_operator(vector[vector.size() - 1]) ||
             is_unary(vector[vector.size() - 1]) ||
             vector[vector.size() - 1].second == Type::start ||
             vector[vector.size() - 1].second == Type::evoid)) {
            if (x2 == Type::minus)
                x2 = Type::uminus;
            if (x2 == Type::plus)
                x2 = Type::uplus;
        }
        stack = s21::Node(0, x2);
    } else if (category == Category::string) {
        int temp = define_trigonometry(str);
        if (temp >= 0)
            stack = s21::Node(0, temp);
    }
}

s21::vector s21::trim_string(const s21::string &str) {
    s21::vector vector;
    s21::string string;
    int category = -1;
    size_t size = str.size();
    for (size_t i = 0; i < size; ++i) {
        if (string.size() > 0) {
            category = define_category(str[i]);
            if (i + 2 < size && define_category(str[i - 1]) == Category::number && str[i] == 'e') {
                // read exponential notation
                string += str[i++];  // read e
                string += str[i++];  // read +/-
                while (define_category(str[i]) == Category::number && i < size)
                    string += str[i++];
                add_element(vector, string);
                string.clear();
            } else if (category == Category::symbol || category != define_category(str[i - 1])) {
                add_element(vector, string);
                string.clear();
            }
        }
        if (i < size)
            string += str[i];
    }
    if (string.size() > 0) {
        add_element(vector, string);
    }
    return vector;
}

// преобразует в польскую нотацию
s21::vector
s21::pol_notation(const s21::vector &vector) {
    s21::vector result;
    s21::vector tempVector;
    size_t size = vector.size();
    for (size_t i = 0; i < size; ++i) {
        if (vector[i].second != Type::evoid) {
            if (vector[i].second == Type::number || vector[i].second == Type::x) {
                result.push_back(vector[i]);
            } else if (vector[i].second == Type::start) {
                tempVector.push_back(vector[i]);
            } else if (vector[i].second == Type::end) {
                for (int j = tempVector.size() - 1; j >= 0 && tempVector[j].second != Type::start; --j) {
                    result.push_back(tempVector[j]);
                    tempVector.pop_back();
                }
                tempVector.pop_back();
            } else {
                for (int j = tempVector.size() - 1;
                     j >= 0 && define_priority(tempVector[j].second) <= define_priority(vector[i].second);
                     --j) {
                    result.push_back(tempVector[j]);
                    tempVector.pop_back();
                }
                tempVector.push_back(vector[i]);
            }
        }
    }
    for (int j = tempVector.size() - 1; j >= 0; --j) {
        result.push_back(tempVector[j]);
        tempVector.pop_back();
    }
    return result;
}

// высчитывает результат из польской нотации
double s21::calc(s21::vector vector, const double &x) {
    from_x_to_number_in_vector(vector, x);
    calc_unary_in_start_vector(vector);
    s21::vector tempVector;
    double result = 0;
    size_t tempVectorSize = 0;
    size_t size = vector.size();
    for (size_t i = 0; i < size && !model.error; ++i) {
        if (is_number(vector[i])) {
            tempVector.push_back(vector[i]);
        } else {
            tempVectorSize = tempVector.size();
            if (is_special_operator(vector[i]) && (tempVectorSize < 2 ||
                                                   !is_number(tempVector[tempVectorSize - 1]) ||
                                                   !is_number(tempVector[tempVectorSize - 2]))) {
                model.error = true;
            } else if ((is_unary(vector[i]) || is_trigonometry(vector[i])) &&
                       (tempVectorSize < 1 || !is_number(tempVector[tempVectorSize - 1]))) {
                model.error = true;
            } else {
                if (tempVectorSize > 1)
                    complete_operation(tempVector[tempVectorSize - 2].first,
                                       tempVector[tempVectorSize - 1].first,
                                       vector[i].second);
                else
                    complete_operation(tempVector[tempVectorSize - 1].first,
                                       tempVector[tempVectorSize - 1].first,
                                       vector[i].second);
            }
            if (is_special_operator(vector[i]))
                tempVector.pop_back();
        }
    }
    if (tempVector.size() > 1)
        model.error = true;
    else if (vector.size() != 0 && model.error == false)
        result = tempVector[0].first;
    else
        result = 0;
    return result;
}

double smart_calc(const char *str, double x) {
    s21::string str2(str);
    double result = 0;
    s21::model.error = false;
    s21::model.vector.clear();
    if (!str2.null_or_whitespace() && !str2.empty()) {
        s21::model.vector = s21::trim_string(str);
        s21::delete_recurring_unary_operation(s21::model.vector);
        s21::correct_count_brakets_in_vector(s21::model.vector);
        if (!s21::model.error) {
            s21::model.vector = s21::pol_notation(s21::model.vector);
            result = s21::calc(s21::model.vector, x);
        }
    }
    return result;
}

double smart_calc_with_old_vector(const double &x) {
    double result = 0;
    if (!s21::model.error && !s21::model.vector.empty())
        result = s21::calc(s21::model.vector, x);
    return result;
}

double Calc(const char *str, double x) {
    return smart_calc(str, x);
};

bool GetError() {
    return s21::model.error;
}

double LastCalc(double x) {
    return smart_calc_with_old_vector(x);
}
