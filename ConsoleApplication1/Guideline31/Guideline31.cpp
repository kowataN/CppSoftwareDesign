#include <cstdlib>
#include <span>
#include <functional>
#include <stdexcept>
#include <utility>

#define GUIDELINE_NAME "Guideline31"
#define NS_GUIDELINE_START namespace G31 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Circle.h
class Circle
{
public:
	explicit Circle(double radius)
		: radius_(radius)
	{
		/* 渡された半径の妥当性を検証 nullチェック*/
	}

	double radius() const { return radius_; }

private:
	double radius_;
};

/////////////////////////////////////////////////////////////////
// Square.h
class Square
{
public:
	explicit Square(double side)
		: side_(side)
	{
	}

	double side() const { return side_; }

private:
	double side_;
};

/////////////////////////////////////////////////////////////////
// Shape.h
class ShapeConcept
{
public:
	virtual ~ShapeConcept() = default;
	virtual void draw() const = 0;
};

struct DefaultDrawer
{
	template<typename T>
	void operator()(T const& obj) const {
		draw(obj);
	}
};

template<typename ShapeT,
		typename DrawStrategy = DefaultDrawer>
class ShapeModel : public ShapeConcept
{
public:
	explicit ShapeModel(ShapeT shape, DrawStrategy drawer = DefaultDrawer{})
		: shape_{ std::move(shape) }
		, drawer_{ std::move(drawer) }
	{}

	void draw() const override { drawer_(shape_); }

private:
	ShapeT shape_;
	DrawStrategy drawer_;
};

class OpenGLDrawStrategy
{
public:
	explicit OpenGLDrawStrategy(){}

	void operator()(Circle const& circle) const;
	void operator()(Square const& square) const;
};

NS_END

void Guideline31()
{
	CLASS_TITLE;

	using Shapes = std::vector<std::unique_ptr<G31::ShapeConcept>>;

	using CircleModel = G31::ShapeModel<G31::Circle, G31::OpenGLDrawStrategy>;
	using SquareModel = G31::ShapeModel<G31::Square, G31::OpenGLDrawStrategy>;

	Shapes shapes{};

	shapes.emplace_back(
		std::make_unique<CircleModel>(
			G31::Circle{2.3}, G31::OpenGLDrawStrategy()));
	shapes.emplace_back(
		std::make_unique<SquareModel>(
			G31::Square{1.2}, G31::OpenGLDrawStrategy()));
	shapes.emplace_back(
		std::make_unique<CircleModel>(
			G31::Circle{4.1}, G31::OpenGLDrawStrategy()));

	for (auto const& shape : shapes)
	{
		shape->draw();
	}

}
