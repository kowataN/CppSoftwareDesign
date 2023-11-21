#pragma once

#include <string>

#include "Item.h"
#include "Money.h"

class ConferenceTicket : public Item
{
public:
    explicit ConferenceTicket(std::string Name, Money Price)
        : m_Name(std::move(Name))
        , m_PriceWithTax(Price * 1.15)
    {}

    std::string const& GetName() const { return m_Name; }
    Money Price() const override { return m_PriceWithTax; }

private:
    std::string m_Name;
    Money m_PriceWithTax;
};
