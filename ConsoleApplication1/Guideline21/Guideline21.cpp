#include <stack>
#include <memory>

#define GUIDELINE_NAME "Guideline21"
#define NS_GUIDELINE_START namespace G21 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// CalculatorCommand.h
class CalculatorCommand
{
public:
    virtual ~CalculatorCommand() = default;

    virtual int execute(int i) const = 0;
    virtual int undo(int i) const = 0;
};

/////////////////////////////////////////////////////////////////
// Add.h
class Add : public CalculatorCommand
{
public:
    explicit Add(int operand) : operand_(operand) {}

    int execute(int i) const override
    {
        return i + operand_;
    }

    int undo(int i) const override
    {
        return i - operand_;
    }

private:
    int operand_{};
};

/////////////////////////////////////////////////////////////////
// Subtract.h
class Subtract : public CalculatorCommand
{
public:
    explicit Subtract(int operand) : operand_(operand) {}

    int execute(int i) const override
    {
        return i - operand_;
    }

    int undo(int i) const override
    {
        return i + operand_;
    }

private:
    int operand_{};
};

/////////////////////////////////////////////////////////////////
// Calculator.h
class Calculator
{
public:
    void compute(std::unique_ptr<CalculatorCommand> command);
    void undoLast();

    int result() const;
    void clear();

private:
    using CommandStack = std::stack<std::unique_ptr<CalculatorCommand>>;

    int current_{};
    CommandStack stack_;
};

void Calculator::compute(std::unique_ptr<CalculatorCommand> command)
{
    current_ = command->execute(current_);
    stack_.push(std::move(command));
}

void Calculator::undoLast()
{
    if (stack_.empty())
    {
        return;
    }

    auto command = std::move(stack_.top());
    stack_.pop();

    current_ = command->undo(current_);
}

int Calculator::result() const
{
    return current_;
}

void Calculator::clear()
{
    current_ = 0;
    CommandStack{}.swap(stack_); // スタックを消去
}

NS_END

void Guideline21()
{
    CLASS_TITLE;

    G21::Calculator calculator{};

    auto op1 = std::make_unique<G21::Add>(3);
    auto op2 = std::make_unique<G21::Add>(7);
    auto op3 = std::make_unique<G21::Subtract>(4);
    auto op4 = std::make_unique<G21::Subtract>(2);

    calculator.compute(std::move(op1)); // 0 + 3
    calculator.compute(std::move(op2)); // 3 + 7
    calculator.compute(std::move(op3)); // 10 - 4
    calculator.compute(std::move(op4)); // 6 - 2

    calculator.undoLast(); // 最後のCommandをundoする

    int const res = calculator.result();
    std::cout << "res: " << res << "\n";
}
