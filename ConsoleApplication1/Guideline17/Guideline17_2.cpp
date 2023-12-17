#include <iostream>
#include <variant>
#include <format>

#define GUIDELINE_NAME "Guideline17_2"
#define NS_START namespace G17_2 {
#define NS_END }

NS_START

/////////////////////////////////////////////////////////////////
// Point.h
struct Point
{
    double x;
    double y;
};

/////////////////////////////////////////////////////////////////
// Circle.h
//#include <Point.h>

class Circle
{
public:
    explicit Circle(double radius)
        : radius_(radius)
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
// Square.h
//#include <Point.h>

class Square
{
public:
    explicit Square(double side)
        : side_(side)
    {
        /* 渡された辺の長さの妥当性を検証 */
    }

    double side() const { return side_; }
    Point  center() const { return center_; }

private:
    double side_;
    Point center_{};
};

NS_END

/////////////////////////////////////////////////////////////////
// Shape.h
//#include <Circle.h>
//#include <Square.h>

using Shape = std::variant<G17_2::Circle, G17_2::Square>;


/////////////////////////////////////////////////////////////////
// Shapes.h
//#include <Shape.h>
#include <vector>

using Shapes = std::vector<Shape>;

/////////////////////////////////////////////////////////////////
// Draw.h
//#include <Circle.h>
//#include <Square.h>
//#include /* 何らかのグラフィックライブラリ */

NS_START

class Draw
{
public:
    void operator()(Circle const& c) const
    {
        /* ... Implementing the logic for drawing a circle ... */
    }
    void operator()(Square const& s) const
    {
        /* ... Implementing the logic for drawing a square ... */
    }
};

NS_END

/////////////////////////////////////////////////////////////////
// DrawAllShapes.h
//#include <Shapes.h>

void drawAllShapes(Shapes const& shapes);


/////////////////////////////////////////////////////////////////
// DrawAllShapes.cpp
//#include <DrawAllShapes.h>
//#include <Draw.h>
#include <variant>

void drawAllShapes(Shapes const& shapes)
{
    for (Shape const& shape : shapes)
    {
        std::visit(G17_2::Draw{}, shape);
    }
}

/////////////////////////////////////////////////////////////////
// Main.cpp

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <DrawAllShapes.h>
#include <cstdlib>

void Guideline17_2()
{
    std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME);

    Shapes shapes;

    shapes.emplace_back(G17_2::Circle{ 2.3 });
    shapes.emplace_back(G17_2::Square{ 1.2 });
    shapes.emplace_back(G17_2::Circle{ 4.1 });

    drawAllShapes(shapes);
}

