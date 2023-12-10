#pragma once

#include <memory>

namespace Guideline12
{
    class Shape
    {
    public:
        void Draw() {}
    };

    class DrawStrategy
    {
    public:
        virtual void Draw(Shape shape) = 0;
    };

    class OpenGLStrategy : public DrawStrategy
    {
    public:
        void Draw(Shape shape) override {}
    };

    class TestStrategy : public DrawStrategy
    {
    public:
        void Draw(Shape shape) override {}
    };

    class Circle
    {
    public:
        Circle(std::unique_ptr<DrawStrategy> strategy) {}
        void Draw() {}

    private:
        std::unique_ptr<DrawStrategy> _strategy;
    };
}

extern void Guideline12_main();
