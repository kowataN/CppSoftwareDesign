
#include <cstdlib>
#include <iostream>
#include <string>
#include <variant>
#include <format>

#define GUIDELINE_NAME "Guideline18"
#define NS_GUIDELINE_START namespace G18 {
#define NS_END }
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// AbstractVisitor.h
class AbstractVisitor
{
public:
    virtual ~AbstractVisitor() = default;
};

/////////////////////////////////////////////////////////////////
// Visitor.h
template< typename T >
class Visitor
{
protected:
    virtual ~Visitor() = default;

public:
    virtual void visit(T const&) const = 0;
};

/////////////////////////////////////////////////////////////////
// Point.h
struct Point
{
    double x;
    double y;
};

/////////////////////////////////////////////////////////////////
// Shape.h
class Shape
{
public:
    virtual ~Shape() = default;

    virtual void accept(AbstractVisitor const& v) = 0;
};

/////////////////////////////////////////////////////////////////
// Circle.h
class Circle : public Shape
{
public:
    explicit Circle(double radius)
        : radius_(radius)
    {
        /* 渡された半径の妥当性を検証 */
    }

    void accept(AbstractVisitor const& v) override {
        if (auto const* cv = dynamic_cast<Visitor<Circle> const*>(&v)) {
            cv->visit(*this);
        }
    }

    double radius() const { return radius_; }
    Point center() const { return center_; }

private:
    double radius_;
    Point center_{};
};

/////////////////////////////////////////////////////////////////
// Square.h
class Square : public Shape
{
public:
    explicit Square(double side)
        : side_(side)
    {
    }

    void accept(AbstractVisitor const& v) override {
        if (auto const* sv = dynamic_cast<Visitor<Square> const*>(&v)) {
            sv->visit(*this);
        }
    }

    double side() const { return side_; }

private:
    double side_;
};


/////////////////////////////////////////////////////////////////
// Draw.h
class Circle;
class Draw : public AbstractVisitor
    , public Visitor<Circle>
    , public Visitor<Square>
{
public:
    void visit(Circle const& c) const override
    {
        /* 円を描画する処理を実装 */
    }
    void visit(Square const& s) const override
    {
        /* 図形を描画する処理を実装 */
    }
};


NS_END

void Guideline18()
{
    CLASS_TITLE;

}
