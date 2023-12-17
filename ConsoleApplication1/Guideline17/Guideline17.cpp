
#include <cstdlib>
#include <iostream>
#include <string>
#include <variant>
#include <format>

#define GUIDELINE_NAME "Guideline17"
#define NS_GUIDELINE_START namespace G17 {
#define NS_END }

NS_GUIDELINE_START

struct Print
{
    void operator()(int value) const
    {
        std::cout << "int: " << value << '\n';
    }

    void operator()(double value) const
    {
        std::cout << "double: " << value << '\n';
    }

    void operator()(std::string const& value) const
    {
        std::cout << "string: " << value << '\n';
    }
};

NS_END

void Guideline17()
{
    std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME);

    std::variant<int, double, std::string> v{};

    v = 42;         // variantにintの42を代入
    v = 3.14;       // variantにdoubleの3.14を代入
    v = 2.71F;      // variantにfloatを代入、doubleへ格上げされる
    v = "Bjarne";   // variantに文字列を"Bjarne"代入
    v = 43;         // variantにintの43を代入

    //int const i = std::get<int>(v);

    //int* const pi = std::get_if<int>(&v);

    std::visit(G17::Print{}, v);
}
