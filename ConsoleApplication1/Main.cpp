﻿#include <conio.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <vector>

// 文字コード設定用に追加
#include <windows.h>

#include "Guideline2/Guideline2.h"
#include "Guideline14/Guideline14.h"
#include "Guideline15/Guideline15.h"
#include "Guideline16/Guideline16.h"
#include "Guideline17/Guideline17.h"

int main()
{
    // 文字コードをUTF-8に変更
    SetConsoleOutputCP(65001);

    Guideline2();
    Guideline14();
    Guideline15();
    Guideline15_2();
    Guideline16();
    Guideline17();
    Guideline17_2();

    _getch();

    return EXIT_SUCCESS;
}
