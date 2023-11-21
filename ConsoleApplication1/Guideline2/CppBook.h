#pragma once

#include <string>

#include "Item.h"
#include "Money.h"

class CppBook : public Item
{
public:
    explicit CppBook(std::string Title, std::string Author, Money Price)
        : m_Title(std::move(Title))
        , m_Author(std::move(Author))
        , m_PriceWithTax(Price * 1.15)
    {}

    std::string const& Title() const { return m_Title; }
    std::string const& Author() const { return m_Author; }
    Money Price() const override { return m_PriceWithTax; }

private:
    std::string m_Title;
    std::string m_Author;
    Money m_PriceWithTax;
};