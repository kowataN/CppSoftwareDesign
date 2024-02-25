#include <cstdlib>
#include <span>
#include <vector>

#define GUIDELINE_NAME "Guideline22"
#define NS_GUIDELINE_START namespace G22 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START
void print(std::span<int> s)
{
    std::cout << " (";
    for (int i : s)
    {
        std::cout << ' ' << i;
    }
    std::cout << " )\n";
}
NS_END

void Guideline22()
{
    CLASS_TITLE;

    std::vector<int> v{ 1,2,3,4 };

    std::vector<int> const w{v};
    std::span<int> const s{v};

    //w[2] = 99; // コンパイルエラー
    s[2] = 99; // 動く

    // prints (1 2 99 4)
    G22::print(s);

    v = {5,6,7,8,9};
    s[2] = 99; // 動く

    // print ?
    G22::print(s);
}
