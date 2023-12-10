#pragma once
namespace Guideline11_3_1
{
    class Strategy
    {
    public:
        virtual void algorithm() = 0;
    };

    class ConcreteStrategyA : public Strategy
    {
    public:
        void algorithm() override {}
    };

    class ConcreteStrategryB : public Strategy
    {
    public:
        void algorithm() override {}
    };

    class Context
    {
    public:
        void context(Strategy* strategy)
        {
            strategy->algorithm();
        }
    };
}

namespace Guideline11_3_2
{
    class Product {};

    class Creator
    {
    public:
        virtual Product* factoryMethod() = 0;
    };

    class ConcreteProduct : Product {};

    class ConcreteCreator : public Creator
    {
    public:
        virtual Product* factoryMethod();
    };
}
