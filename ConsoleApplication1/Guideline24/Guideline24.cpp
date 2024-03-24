#include <memory>
#include <vector>

#define GUIDELINE_NAME "Guideline24"
#define NS_GUIDELINE_START namespace G24 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Duck.h
class Duck
{
public:
	virtual ~Duck() = default;

	virtual void quack() = 0;
	virtual void fly() = 0;
};

/////////////////////////////////////////////////////////////////
// MallardDuck.h
class MallardDuck : public Duck
{
public:
	// Duck を介して継承されました
	void quack() override
	{
		std::cout << "MallardDuck::quack" << "\n";
	}

	void fly() override
	{
	}
};

/////////////////////////////////////////////////////////////////
// Turkey.h
class Turkey
{
public:
	virtual ~Turkey() = default;
	virtual void gobble() = 0;
	virtual void fly() = 0;
};

/////////////////////////////////////////////////////////////////
// WildTurkey.h
class WildTurkey : public Turkey
{
	// Turkey を介して継承されました
	void gobble() override
	{
		std::cout << "WildTurkey::gobble" << "\n";
	}

	void fly() override
	{
		std::cout << "WildTurkey::fly" << "\n";
	}
};

/////////////////////////////////////////////////////////////////
// TurkeyAdapter.h
class TurkeyAdapter : public Duck
{
public:
	explicit TurkeyAdapter(std::unique_ptr<Turkey> turkey)
		: turkey_{ std::move(turkey) }
	{
	}

	// Duck を介して継承されました
	void quack() override
	{	
		turkey_->gobble();
	}

	void fly() override
	{
		turkey_->fly();
	}

private:
	std::unique_ptr<Turkey> turkey_;
};

NS_END

using DuckChoir = std::vector<std::unique_ptr<G24::Duck>>;

void give_concert(DuckChoir const& duck_choir)
{
	for (auto const& duck : duck_choir)
	{
		duck->quack();
	}
}

void Guideline24()
{
	CLASS_TITLE;

	DuckChoir duck_choir{};

	duck_choir.push_back(std::make_unique<G24::MallardDuck>());
	duck_choir.push_back(std::make_unique<G24::MallardDuck>());
	duck_choir.push_back(std::make_unique<G24::MallardDuck>());
	
	auto turkey = std::make_unique<G24::WildTurkey>();
	auto turkey_in_disguise = std::make_unique<G24::TurkeyAdapter>(std::move(turkey));
	duck_choir.push_back(std::move(turkey_in_disguise));

	give_concert(duck_choir);
}
