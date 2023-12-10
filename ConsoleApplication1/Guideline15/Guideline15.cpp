#include <iostream>

#define NS_G15_START namespace G15 {
#define NS_G15_END }

NS_G15_START

// 手続き型プログラミングの解

/////////////////////////////////////////////////////////////////
// Point.h
struct Point
{
    double x;
    double y;
};

/////////////////////////////////////////////////////////////////
// Shape.h
enum ShapeType
{
    circle,
    square,
};

class Shape
{
protected:
    explicit Shape(ShapeType type)
        : type_(type)
    {}

public:
    virtual ~Shape() = default;

    ShapeType getType() const { return type_; }

private:
    ShapeType type_;
};

/////////////////////////////////////////////////////////////////
// Circle.h
//#include <Point.h>
//#include <Shape.h>

class Circle : public Shape
{
public:
    explicit Circle(double radius)
        : Shape(circle)
        , radius_(radius)
    {
        /* 渡された半径の妥当性を検証 */
    }

    double radius() const { return radius_; }
    Point  center() const { return center_; }

private:
    double radius_;
    Point center_{};
};

NS_G15_END

/////////////////////////////////////////////////////////////////
// DrawCircle.h
NS_G15_START
class Circle;
NS_G15_END

void draw_G15(G15::Circle const&);

/////////////////////////////////////////////////////////////////
// DrawCircle.cpp
//#include <Circle.h>
//#include <DrawCircle.h>
//#include /* 何らかのグラフィックライブラリ */

void draw_G15(G15::Circle const& circle)
{
    // 円を描画する処理を実装
    std::cout << "円を描画\n";
}

NS_G15_START

/////////////////////////////////////////////////////////////////
// Square.h

//#include <Shape.h>
//#include <Point.h>

class Square : public Shape
{
public:
    explicit Square(double side)
        : Shape(square)
        , side_(side)
    {
        /* 渡された辺の長さの妥当性を検証 */
    }

    double side() const { return side_; }
    Point  center() const { return center_; }

private:
    double side_;
    Point center_{}; // 中心に限らず、頂点でもよ
};

NS_G15_END

/////////////////////////////////////////////////////////////////
// DrawSquare.h
NS_G15_START
class Square;
NS_G15_END

void draw_G15(G15::Square const& square);

/////////////////////////////////////////////////////////////////
// DrawSquare.cpp
//#include <DrawSquare.h>
//#include <Square.h>
//#include /* 何らかのグラフィックライブラリ */

void draw_G15(G15::Square const& square)
{
    // 正方形を描画する処理を実装
    std::cout << "正方形を描画\n";
}

/////////////////////////////////////////////////////////////////
// DrawAllShapes.h
#include <memory>
#include <vector>
NS_G15_START
class Shape;
NS_G15_END

void drawAllShapes_G15(std::vector<std::unique_ptr<G15::Shape>> const& shapes);

/////////////////////////////////////////////////////////////////
// DrawAllShapes.cpp
//#include <DrawAllShapes.h>
//#include <Circle.h>
//#include <Square.h>

void drawAllShapes_G15(std::vector<std::unique_ptr<G15::Shape>> const& shapes)
{
    for (auto const& shape : shapes)
    {
        switch (shape->getType())
        {
        case G15::circle:
            draw_G15(static_cast<G15::Circle const&>(*shape));
            break;
        case G15::square:
            draw_G15(static_cast<G15::Square const&>(*shape));
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////
// Guideline15

#include <cstdlib>
#include <memory>
#include <vector>

void Guideline15()
{
    std::cout << "\nGuideline15 ---------\n";

    using Shapes = std::vector<std::unique_ptr<G15::Shape>>;

    // Creating some shapes
    Shapes shapes{};
    shapes.emplace_back(std::make_unique<G15::Circle>(2.3));
    shapes.emplace_back(std::make_unique<G15::Square>(1.2));
    shapes.emplace_back(std::make_unique<G15::Circle>(4.1));

    // Drawing all shapes
    drawAllShapes_G15(shapes);
}
