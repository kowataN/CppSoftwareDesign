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
        /* �n���ꂽ���a�̑Ó��������� */
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
//#include /* ���炩�̃O���t�B�b�N���C�u���� */

void draw(Circle const& circle)
{
    // �~��`�悷�鏈��������
    std::cout << "�~��`��\n";
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
        /* �n���ꂽ�ӂ̒����̑Ó��������� */
    }

    double side() const { return side_; }
    Point  center() const { return center_; }

private:
    double side_;
    Point center_{}; // ���S�Ɍ��炸�A���_�ł���
};

/////////////////////////////////////////////////////////////////
// DrawSquare.h
class Square;

void draw(Square const& square);

/////////////////////////////////////////////////////////////////
// DrawSquare.cpp
//#include <DrawSquare.h>
//#include <Square.h>
//#include /* ���炩�̃O���t�B�b�N���C�u���� */

void draw(Square const& square)
{
    // �����`��`�悷�鏈��������
    std::cout << "�����`��`��\n";
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
