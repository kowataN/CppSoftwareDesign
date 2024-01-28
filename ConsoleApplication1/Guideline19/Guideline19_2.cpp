#define GUIDELINE_NAME "Guideline19_2"
#define NS_GUIDELINE_START namespace G19_2 {
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
// Circle.h
class Circle : public Shape
{
public:
    explicit Circle(double radius)
        : radius_(radius)
    {
        /* 渡された半径の妥当性を検証 */
    }

    double radius() const { return radius_; }
    Point center() const { return center_; }

private:
    double radius_;
    Point center_{};
};

/////////////////////////////////////////////////////////////////
// OpenGLCircle.h
class OpenGLCircle : public Circle
{
public:
    explicit OpenGLCircle(double radius)
        : Circle(radius)
    {}

    void draw(/* 何らかの引数 */) const override
    {
        /* OpenGLを用いた正方形を描画する処理を実装 */
    }
};

/////////////////////////////////////////////////////////////////
// Square.h
class Square : public Shape
{
public:
    explicit Square(double side)
        : side_(side)
    {
        /* 渡された辺の長さの妥当性を検証 */
    }

    double side() const { return side_; }
    Point center() const { return center_; }

private:
    double side_;
    Point center_{};
};

/////////////////////////////////////////////////////////////////
// OpenGLSquare.h
class OpenGLSquare : public Square
{
public:
    explicit OpenGLSquare(double side)
        : Square(side)
    {}

    void draw(/* 何らかの引数 */) const override
    {
        /* OpenGLを用いた正方形を描画する処理を実装 */
    }
};






NS_END
