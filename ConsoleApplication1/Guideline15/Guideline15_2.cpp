#include <iostream>

#define NS_G15_2_START namespace G15_2 {
#define NS_G15_2_END }

NS_G15_2_START

// オブジェクト指向の解

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
    Shape() = default;

    virtual ~Shape() = default;

    virtual void draw() const = 0;
};

/////////////////////////////////////////////////////////////////
// Circle.h
//#include <Point.h>
//#include <Shape.h>

class Circle : public Shape
{
public:
    explicit Circle(double radius)
        : radius_(radius)
    {
        /* 渡された半径の妥当性を検証 */
    }

    double radius() const { return radius_; }
    Point  center() const { return center_; }

    void draw() const override;

private:
    double radius_;
    Point center_{};
};

/////////////////////////////////////////////////////////////////
// Circle.cpp
//#include <Circle.h>
//#include /* some graphics library */

void Circle::draw() const
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
        : side_(side)
    {
        /* 渡された辺の長さの妥当性を検証 */
    }

    double side() const { return side_; }
    Point  center() const { return center_; }

    void draw() const override;

private:
    double side_;
    Point center_{};
};

/////////////////////////////////////////////////////////////////
// Square.cpp
//#include <Square.h>
//#include /* some graphics library */

void Square::draw() const
{
    // 正方形を描画する処理を実装
    std::cout << "正方形を描画\n";
}

NS_G15_2_END

/////////////////////////////////////////////////////////////////
// DrawAllShapes.h
#include <memory>
#include <vector>
NS_G15_2_START
class Shape;
NS_G15_2_END

void drawAllShapes_G15_2(std::vector<std::unique_ptr<G15_2::Shape>> const& shapes);

/////////////////////////////////////////////////////////////////
// DrawAllShapes.cpp
//#include <DrawAllShapes.h>
//#include <Shape.h>

void drawAllShapes_G15_2(std::vector<std::unique_ptr<G15_2::Shape>> const& shapes)
{
    for (auto const& shape : shapes)
    {
        shape->draw();
    }
}


/////////////////////////////////////////////////////////////////
// Guideline15_2
#include <cstdlib>
#include <memory>
#include <vector>

void Guideline15_2()
{
    std::cout << "\nGuideline15_2 ---------\n";

    using Shapes = std::vector<std::unique_ptr<G15_2::Shape>>;

    // Creating some shapes
    Shapes shapes{};
    shapes.emplace_back(std::make_unique<G15_2::Circle>(2.3));
    shapes.emplace_back(std::make_unique<G15_2::Square>(1.2));
    shapes.emplace_back(std::make_unique<G15_2::Circle>(4.1));

    // Drawing all shapes
    drawAllShapes_G15_2(shapes);
}
