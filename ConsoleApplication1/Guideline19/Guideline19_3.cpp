#include <memory>
#include <utility>

#define GUIDELINE_NAME "Guideline19_3"
#define NS_GUIDELINE_START namespace G19_3 {
#define NS_END }
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

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
    virtual ~Shape() = default;

    virtual void draw(/* 何らかの引数 */) const = 0;
};

/////////////////////////////////////////////////////////////////
// DrawStrategy.h
class DrawStrategy
{
public:
    virtual ~DrawStrategy() = default;

    virtual void draw(class Circle const& circle /* 何らかの引数 */) const = 0;
    virtual void draw(class Square const& square /* 何らかの引数 */) const = 0;
};

/////////////////////////////////////////////////////////////////
// Circle.h
class Circle : public Shape
{
public:
    explicit Circle(double radius, std::unique_ptr<DrawStrategy> drawer)
        : radius_(radius)
        , drawer_(std::move(drawer))
    {
        /* 渡された半径の妥当性を検証 nullチェック*/
    }

    double radius() const { return radius_; }
    Point center() const { return center_; }

    void draw(/* 何らかの引数 */) const override
    {
        drawer_->draw(*this /* 何らかの引数 */);
    }

private:
    double radius_;
    Point center_{};
    std::unique_ptr<DrawStrategy> drawer_;
};

/////////////////////////////////////////////////////////////////
// Square.h
class Square : public Shape
{
public:
    explicit Square(double side, std::unique_ptr<DrawStrategy> drawer)
        : side_(side)
    {
        /* 渡された辺の長さの妥当性を検証 */
    }

    double side() const { return side_; }
    Point center() const { return center_; }

    void draw(/* 何らかの引数 */) const override
    {
        drawer_->draw(*this /* 何らかの引数 */);
    }

private:
    double side_;
    Point center_{};
    std::unique_ptr<DrawStrategy> drawer_;
};


NS_END
