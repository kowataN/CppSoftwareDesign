#include "Guideline14.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <variant>

struct Print
{
    void operator()(int i) const {
        std::cout << "int: " << i << "\n";
    }
    void operator()(double d) const {
        std::cout << "double: " << d << "\n";
    }
    void operator()(std::string const& s) const {
        std::cout << "string: " << s << "\n";
    }
};

void Guideline14()
{
    std::variant<int, double, std::string> v{};

    v = "C++ Variant example";
    v = 1000.0123;

    std::visit(Print{}, v);
}
