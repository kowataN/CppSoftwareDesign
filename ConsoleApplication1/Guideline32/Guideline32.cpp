#include <cstdlib>
#include <span>
#include <functional>
#include <stdexcept>
#include <utility>

#include <any>
#include <memory>
using namespace std::string_literals;

#define GUIDELINE_NAME "Guideline32"
#define NS_GUIDELINE_START namespace G32 {
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
	{}

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
	{}

	double side() const { return side_; }

private:
	double side_;
};

/////////////////////////////////////////////////////////////////
// ShpapeConcept
namespace detail {

class ShapeConcept
{
public:
	virtual ~ShapeConcept() = default;
	virtual void draw() const = 0;
	virtual std::unique_ptr<ShapeConcept> clone() const = 0;
};

template<typename ShapeT, typename DrawStrategy>
class OwningShapeModel : public ShapeConcept
{
public:
	explicit OwningShapeModel(ShapeT shape, DrawStrategy drawer)
		: shape_{ std::move(shape) }
		, drawer_{ std::move(drawer)}
	{}

	void draw() const override { drawer_(shape_); }

	std::unique_ptr<ShapeConcept> clone() const override
	{
		return std::make_unique<OwningShapeModel>(*this);
	}

private:
	ShapeT shape_;
	DrawStrategy drawer_;
};

}// namespace detail;

/////////////////////////////////////////////////////////////////
// Shpape
class Shape
{
public:
	template<typename ShapeT, typename DrawerStrategy>
	Shape(ShapeT shape, DrawerStrategy drawer)
	{
		using Model = detail::OwningShapeModel<ShapeT, DrawerStrategy>;
		pimpl_ = std::make_unique<Model>(std::move(shape), std::move(drawer));
	}

	Shape(Shape const& other)
		: pimpl_(other.pimpl_->clone())
	{}

	Shape& operator=(Shape const& other)
	{
		Shape copy(other);
		pimpl_.swap(copy.pimpl_);
		return *this;
	}

	~Shape() = default;
	Shape(Shape&&) = default;
	Shape& operator=(Shape&&) = default;

private:
	friend void draw(Shape const& shape)
	{
		shape.pimpl_->draw();
	}

private:
	std::unique_ptr<detail::ShapeConcept> pimpl_;
};

NS_END

void Guideline32()
{
	CLASS_TITLE;

	G32::Circle circle{ 3.14 };

	auto drawer = [](G32::Circle const& c) {  };

	G32::Shape shape1(circle, drawer);

	draw(shape1);

	G32::Shape shape2(shape1);

	draw(shape2);
}
