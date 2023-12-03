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
class Shape_G15_2
{
public:
    Shape_G15_2() = default;

    virtual ~Shape_G15_2() = default;

    virtual void draw() const = 0;
};

/////////////////////////////////////////////////////////////////
// Circle.h
//#include <Point.h>
//#include <Shape.h>

class Circle : public Shape_G15_2
{
public:
    explicit Circle(double radius)
        : radius_(radius)
    {
        /* “n‚³‚ê‚½”¼Œa‚Ì‘Ã“–«‚ğŒŸØ valid */
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
    // ‰~‚ğ•`‰æ‚·‚éˆ—‚ğÀ‘•
    std::cout << "‰~‚ğ•`‰æ\n";
}

/////////////////////////////////////////////////////////////////
// Square.h
//#include <Shape.h>
//#include <Point.h>

class Square : public Shape_G15_2
{
public:
    explicit Square(double side)
        : side_(side)
    {
        /* “n‚³‚ê‚½•Ó‚Ì’·‚³‚Ì‘Ã“–«‚ğŒŸØ */
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
    // ³•ûŒ`‚ğ•`‰æ‚·‚éˆ—‚ğÀ‘•
    std::cout << "³•ûŒ`‚ğ•`‰æ\n";
}

/////////////////////////////////////////////////////////////////
// DrawAllShapes.h
#include <memory>
#include <vector>
class Shape_G15_2;

void drawAllShapes_G15_2(std::vector<std::unique_ptr<Shape_G15_2>> const& shapes);

/////////////////////////////////////////////////////////////////
// DrawAllShapes.cpp
//#include <DrawAllShapes.h>
//#include <Shape.h>

void drawAllShapes_G15_2(std::vector<std::unique_ptr<Shape_G15_2>> const& shapes)
{
    for (auto const& shape : shapes)
    {
        //shape->draw(); // —áŠO‚ª”­¶‚·‚é
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

    using Shapes = std::vector<std::unique_ptr<Shape_G15_2>>;

    // Creating some shapes
    Shapes shapes{};
    shapes.emplace_back(std::make_unique<Circle>(2.3));
    shapes.emplace_back(std::make_unique<Square>(1.2));
    shapes.emplace_back(std::make_unique<Circle>(4.1));

    // Drawing all shapes
    drawAllShapes_G15_2(shapes);
}
