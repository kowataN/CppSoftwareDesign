#include <cstdlib>
#include <span>
#include <functional>
#include <utility>

#define GUIDELINE_NAME "Guideline23"
#define NS_GUIDELINE_START namespace G23 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START
void foo(int i)
{
    std::cout << "foo: " << i << "\n";
}

/////////////////////////////////////////////////////////////////
// Shape.h
class Shape
{
public:
    virtual ~Shape() = default;

    virtual void draw(/* 何らかの引数 */) const = 0;
};

/////////////////////////////////////////////////////////////////
// Circle.h
class Circle : public Shape
{
public:
    using DrawStrategy = std::function<void(Circle const& /* 何らかの引数 */)>;

    explicit Circle(double radius, DrawStrategy drawer)
        : radius_(radius)
        , drawer_(std::move(drawer))
    {
        /* 渡された半径の妥当性を検証 nullチェック*/
    }

    void draw(/* 何らかの引数 */) const override
    {
        drawer_(*this /* 何らかの引数 */);
    }

    double radius() const { return radius_; }

private:
    double radius_;
    DrawStrategy drawer_;
};

/////////////////////////////////////////////////////////////////
// Square.h
class Square : public Shape
{
public:
    using DrawStrategy = std::function<void(Square const& /* 何らかの引数 */)>;

    explicit Square(double side, DrawStrategy drawer)
        : side_(side)
        , drawer_(std::move(drawer))
    {
        /* 渡された辺の長さの妥当性を検証 */
    }

    void draw(/* 何らかの引数 */) const override
    {
        drawer_(*this /* 何らかの引数 */);
    }

    double side() const { return side_; }

private:
    double side_;
    DrawStrategy drawer_;
};

NS_END

void Guideline23()
{
    CLASS_TITLE;

    std::function<void(int)> f{};

    f = [](int i) {
        std::cout << "lambda: " << i << "\n";
    };

    f(1);

    auto g = f; // コピー

    f = G23::foo;

    f(2);
    g(3);
}
