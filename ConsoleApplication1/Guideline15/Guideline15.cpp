#include <iostream>

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

/////////////////////////////////////////////////////////////////
// DrawCircle.h
class Circle;
void draw(Circle const&);

/////////////////////////////////////////////////////////////////
// DrawCircle.cpp
//#include <Circle.h>
//#include <DrawCircle.h>
//#include /* 何らかのグラフィックライブラリ */

void draw(Circle const& circle)
{
    // 円を描画する処理を実装
    std::cout << "円を描画\n";
}

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

/////////////////////////////////////////////////////////////////
// DrawSquare.h
class Square;

void draw(Square const& square);

/////////////////////////////////////////////////////////////////
// DrawSquare.cpp
//#include <DrawSquare.h>
//#include <Square.h>
//#include /* 何らかのグラフィックライブラリ */

void draw(Square const& square)
{
    // 正方形を描画する処理を実装
    std::cout << "正方形を描画\n";
}

/////////////////////////////////////////////////////////////////
// DrawAllShapes.h
#include <memory>
#include <vector>
class Shape;

void drawAllShapes(std::vector<std::unique_ptr<Shape>> const& shapes);

/////////////////////////////////////////////////////////////////
// DrawAllShapes.cpp
//#include <DrawAllShapes.h>
//#include <Circle.h>
//#include <Square.h>

void drawAllShapes(std::vector<std::unique_ptr<Shape>> const& shapes)
{
    for (auto const& shape : shapes)
    {
        switch (shape->getType())
        {
        case circle:
            draw(static_cast<Circle const&>(*shape));
            break;
        case square:
            draw(static_cast<Square const&>(*shape));
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

    using Shapes = std::vector<std::unique_ptr<Shape>>;

    // Creating some shapes
    Shapes shapes{};
    shapes.emplace_back(std::make_unique<Circle>(2.3));
    shapes.emplace_back(std::make_unique<Square>(1.2));
    shapes.emplace_back(std::make_unique<Circle>(4.1));

    // Drawing all shapes
    drawAllShapes(shapes);
}
