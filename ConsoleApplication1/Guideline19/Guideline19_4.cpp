#include <memory>
#include <utility>

#define GUIDELINE_NAME "Guideline19_4"
#define NS_GUIDELINE_START namespace G19_4 {
#define NS_END }
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Shape.h
class Shape
{
public:
	virtual ~Shape() = default;

	virtual void draw(/* 何らかの引数 */) const = 0;
};

/////////////////////////////////////////////////////////////////
// DrawCircleStrategy.h
class Circle;
class DrawCircleStrategy
{
public:
	virtual ~DrawCircleStrategy() = default;
	virtual void draw(Circle const& circle /* 何らかの引数 */) const = 0;
};

/////////////////////////////////////////////////////////////////
// Circle.h
class Circle : public Shape
{
public:
	explicit Circle(double radius, std::unique_ptr<DrawCircleStrategy> drawer)
		: radius_(radius)
		, drawer_(std::move(drawer))
	{
		/* 渡された半径の妥当性を検証 nullチェック*/
	}

	void draw(/* 何らかの引数 */) const override
	{
		drawer_->draw(*this /* 何らかの引数 */);
	}

	double radius() const { return radius_; }

private:
	double radius_;
	std::unique_ptr<DrawCircleStrategy> drawer_;
};

/////////////////////////////////////////////////////////////////
// DrawSquareStrategy.h
class Square;
class DrawSquareStrategy
{
public:
	virtual ~DrawSquareStrategy() = default;
	virtual void draw(Square const& square /* 何らかの引数 */) const = 0;
};

/////////////////////////////////////////////////////////////////
// Square.h
class Square : public Shape
{
public:
	explicit Square(double side, std::unique_ptr<DrawSquareStrategy> drawer)
		: side_(side)
		, drawer_(std::move(drawer))
	{
		/* 渡された辺の長さの妥当性を検証 */
	}
   
	void draw(/* 何らかの引数 */) const override
	{
		drawer_->draw(*this /* 何らかの引数 */);
	}

	double side() const { return side_; }

private:
	double side_;
	std::unique_ptr<DrawSquareStrategy> drawer_;
};


NS_END
