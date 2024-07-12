#include "calculate.h"
#include <stdexcept> // Pro výjimky

int secti(int a, int b) {
    return a + b;
}

int odecti(int a, int b) {
    return a - b;
}

int nasob(int a, int b) {
    return a * b;
}

double del(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Dělení nulou není povoleno");
    }
    return static_cast<double>(a) / b;
}

int mocni(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; ++i) {
        result *= a;
    }
    return result;
}

int procenta(int chyb, int celkem) {
    return chyb * 100 / celkem;
}

