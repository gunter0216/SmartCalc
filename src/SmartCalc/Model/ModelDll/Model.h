#ifndef S21_MODEL_H_
#define S21_MODEL_H_

#include "s21_node.h"
#include "s21_string.h"
#include "s21_vector.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <string>
#include <vector>

namespace s21 {
namespace Category {
enum {
    symbol,
    number,
    string
};
}
namespace Type {
enum {
    number,
    start,
    end,
    plus,
    minus,
    mul,
    div,
    mod,
    pow,
    uplus,
    uminus,
    cos,
    sin,
    tan,
    acos,
    asin,
    atan,
    sqrt,
    ln,
    log,
    evoid,
    x
};
}  // namespace Type

struct Model {
    bool error = false;
    s21::vector vector;
} model;

s21::vector trim_string(const s21::string &str);
s21::vector pol_notation(const s21::vector &vector);
double calc(s21::vector vector, const double &x);
void createElement(s21::vector &vector, s21::string &str, s21::Node &stack);
void add_element(s21::vector &vector, s21::string &str);
void correct_count_brakets_in_vector(s21::vector &vector);
std::pair<int, int> count_brakets_in_vector(const s21::vector &vector);
void complete_operation(double &x1, double &x2, const int &operation);
void calc_unary_in_start_vector(s21::vector &vector);
void from_x_to_number_in_vector(s21::vector &vector, const double &x);
void push_close_braket_in_vector(s21::vector &vector, const int &count);
void delete_recurring_unary_operation(s21::vector &vector);
bool is_special_operator(const s21::Node &item);
bool is_trigonometry(const s21::Node &item);
bool is_number(const s21::Node &item);
bool is_number(char x);
bool is_unary(const s21::Node &item);

bool is_correct_string_for_convert_to_number(const s21::string &str);
int define_special_symbol(char x);
int define_trigonometry(const s21::string &str);
int define_category(char x);
int define_priority(int x);

}  // namespace s21

double smart_calc(const char *str, double x);
double smart_calc_with_old_vector(const double &x);

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport) 
#else
#define DLLEXPORT
#endif

extern "C" DLLEXPORT double Calc(const char *str, double x);

extern "C" DLLEXPORT double LastCalc(double x);

extern "C" DLLEXPORT bool GetError();

#endif  // S21_MODEL_H_
