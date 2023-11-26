// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "Guideline2.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <numeric>
#include <vector>

#include "CppBook.h"
#include "ConferenceTicket.h"

void Guideline2()
{
    //std::vector<std::unique_ptr<Item>> Items {};

    //Items.emplace_back(std::make_unique<CppBook>("Effective C++", "Scott", 19.99));
    //Items.emplace_back(std::make_unique<CppBook>("C++ Templates", "Scott", 49.99));
    //Items.emplace_back(std::make_unique<ConferenceTicket>("C++Con", 999.0));
    //Items.emplace_back(std::make_unique<ConferenceTicket>("Metting C++", 699.0));
    //Items.emplace_back(std::make_unique<ConferenceTicket>("C++ On Sea", 499.0));

    //Money const TotalPrice = std::accumulate(begin(Items), end(Items), Money{},
    //    [](Money Accu, auto const& Item)
    //    {
    //        return Accu + Item->Price();
    //    }
    //);
}
