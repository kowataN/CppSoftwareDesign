#pragma once

#include "Money.h"

class Item
{
public:
    virtual ~Item() = default;
    virtual Money Price() const = 0;
};