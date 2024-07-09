#include <iostream>
#include "../api/calculate.h"  // Include hlavičkového souboru s deklaracemi funkcí

int main() {
    int a, b;
    std::cout << "Zadejte první číslo: ";
    std::cin >> a;
    std::cout << "Zadejte druhé číslo: ";
    std::cin >> b;

    std::cout << "secti(" << a << ", " << b << ") = " << secti(a, b) << std::endl;
    std::cout << "odecti(" << a << ", " << b << ") = " << odecti(a, b) << std::endl;
    std::cout << "nasob(" << a << ", " << b << ") = " << nasob(a, b) << std::endl;

    try {
        std::cout << "del(" << a << ", " << b << ") = " << del(a, b) << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "mocni(" << a << ", " << b << ") = " << mocni(a, b) << std::endl;

    return 0;
}

