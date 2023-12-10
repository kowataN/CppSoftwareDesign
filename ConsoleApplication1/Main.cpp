#include <conio.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <vector>

#include "Guideline2/Guideline2.h"
#include "Guideline14/Guideline14.h"
#include "Guideline15/Guideline15.h"
#include "Guideline16/Guideline16.h"

int main()
{
    Guideline2();
    Guideline14();
    Guideline15();
    Guideline15_2();
    Guideline16();

    _getch();

    return EXIT_SUCCESS;
}
