#include <stack>
#include <memory>

#define GUIDELINE_NAME "Guideline21_2"
#define NS_GUIDELINE_START namespace G21_2 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Command.h
class Command {};

/////////////////////////////////////////////////////////////////
// FormattingCommand.h
class FormattingCommand : public Command {};

/////////////////////////////////////////////////////////////////
// PrintCommand.h
class PrintCommand : public Command {};

/////////////////////////////////////////////////////////////////
// ThreadPool.h
class ThreadPool
{
public:
    explicit ThreadPool(size_t numThreads);

    inline bool isEmpty() const;
    inline size_t size() const;
    inline size_t active() const;
    inline size_t ready() const;

    void schedule(std::unique_ptr<Command> command);

    void wait();
};


ThreadPool::ThreadPool(size_t numThreads)
{
}

inline bool ThreadPool::isEmpty() const
{
    return false;
}

inline size_t ThreadPool::active() const
{
    return size_t();
}

inline size_t ThreadPool::ready() const
{
    return size_t();
}

void ThreadPool::schedule(std::unique_ptr<Command> command)
{
}

void ThreadPool::wait()
{
}

NS_END

void Guideline21_2()
{
    CLASS_TITLE;

    G21_2::ThreadPool threadpool(2);

    threadpool.schedule(
        std::make_unique<G21_2::FormattingCommand>()
    );
    threadpool.schedule(
        std::make_unique<G21_2::PrintCommand>()
    );

    threadpool.wait();
}
