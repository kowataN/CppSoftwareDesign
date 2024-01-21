#include <iostream>
#include <format>

#define GUIDELINE_NAME "Guideline16"
#define NS_START namespace G16 {
#define NS_END }
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_START

/////////////////////////////////////////////////////////////////
// ShapeVisitor.h
class Circle;
class Square;

class ShapeVisitor
{
public:
    virtual ~ShapeVisitor() = default;

    virtual void visit(Circle const& /*, ...*/) const = 0;
    virtual void visit(Square const& /*, ...*/) const = 0;
    // Possibly more visit() functions, one for each concrete shape
};

/////////////////////////////////////////////////////////////////
// Shape.h
//#include <ShapeVisitor.h>

class Shape
{
public:
    virtual ~Shape() = default;
    virtual void accept(ShapeVisitor const& v) = 0;
};


/////////////////////////////////////////////////////////////////
// Circle.h
//#include <Shape.h>

class Circle : public Shape
{
public:
    explicit Circle(double radius)
        : radius_(radius)
    {
        /*  指定された半径が有効であることを確認する */
    }

    void accept(ShapeVisitor const& v) override { v.visit(*this); }

    double radius() const { return radius_; }

private:
    double radius_;
};


/////////////////////////////////////////////////////////////////
// Square.h
//#include <Shape.h>

class Square : public Shape
{
public:
    explicit Square(double side)
        : side_(side)
    {
        /* 指定された辺の長さが有効であることを確認する */
    }

    void accept(ShapeVisitor const& v) override { v.visit(*this); }

    double side() const { return side_; }

private:
    double side_;
};


/////////////////////////////////////////////////////////////////
// Draw.h
//#include <Circle.h>
//#include <ShapeVisitor.h>
//#include <Square.h>

class Draw : public ShapeVisitor
{
public:
    void visit(Circle const& c /*, ...*/) const override
    {
        // 円を描くロジックの実装
        std::cout << "円を描画\n";
    }

    void visit(Square const& s /*, ...*/) const override
    {
        // 正方形を描画するロジックの実装
        std::cout << "正方形をを描画\n";
    }

    // Possibly more visit() functions, one for each concrete shape
};

NS_END


/////////////////////////////////////////////////////////////////
// DrawAllShapes.h
#include <memory>
#include <vector>
NS_START
class Shape;
NS_END

void drawAllShapes_G16(std::vector<std::unique_ptr<G16::Shape>> const& shapes);

/////////////////////////////////////////////////////////////////
// DrawAllShapes.cpp
//#include <DrawAllShapes.h>
//#include <Draw.h>
//#include <Shape.h>

void drawAllShapes_G16(std::vector<std::unique_ptr<G16::Shape>> const& shapes)
{
    for (auto const& shape : shapes)
    {
        shape->accept(G16::Draw{});
    }
}


/////////////////////////////////////////////////////////////////
// Guideline16
//#include <Circle.h>
//#include <Square.h>
//#include <DrawAllShapes.h>
#include <cstdlib>
#include <memory>
#include <vector>

void Guideline16()
{
    CLASS_TITLE;

    using Shapes = std::vector<std::unique_ptr<G16::Shape>>;

    Shapes shapes{};

    // Creating some shapes
    shapes.emplace_back(std::make_unique<G16::Circle>(2.3));
    shapes.emplace_back(std::make_unique<G16::Square>(1.2));
    shapes.emplace_back(std::make_unique<G16::Circle>(4.1));

    // Drawing all shapes
    drawAllShapes_G16(shapes);
}
