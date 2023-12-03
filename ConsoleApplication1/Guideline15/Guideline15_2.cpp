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
        /* �n���ꂽ���a�̑Ó��������� valid */
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
    // �~��`�悷�鏈��������
    std::cout << "�~��`��\n";
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
        /* �n���ꂽ�ӂ̒����̑Ó��������� */
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
    // �����`��`�悷�鏈��������
    std::cout << "�����`��`��\n";
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
        //shape->draw(); // ��O����������
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
