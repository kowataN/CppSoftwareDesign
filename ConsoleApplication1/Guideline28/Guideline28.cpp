#include <vector>
#include <memory>
#include <string>
#include <numeric>
#include <iosfwd>
#include <iterator>
#include <array>
#include <utility>
#include <cstdlib>

#define GUIDELINE_NAME "Guideline28"
#define NS_GUIDELINE_START namespace G28 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Engine.h
class Engine
{
public:
	virtual ~Engine() = default;

	virtual void start() = 0;
	virtual void end() = 0;

private:
};

/////////////////////////////////////////////////////////////////
// ElectricEngine.h
class ElectricEngine : public Engine
{
public:
	virtual void start() override;
	virtual void end() override;
};

/////////////////////////////////////////////////////////////////
// ElectricEngine.cpp
void ElectricEngine::start() {}
void ElectricEngine::end() {}

/////////////////////////////////////////////////////////////////
// Car.h
class Car
{
protected:
	explicit Car(std::unique_ptr<Engine> engine)
		: pimpl_(std::move(engine))
	{}

public:
	virtual ~Car() = default;
	virtual void drive() = 0;

protected:
	Engine* getEngine() { return pimpl_.get(); }
	Engine const* getEnginr() const { return pimpl_.get(); }

private:
	std::unique_ptr<Engine> pimpl_;
};

/////////////////////////////////////////////////////////////////
// ElectricCar.h
class ElectricCar : public Car
{
public:
	explicit ElectricCar();

	void drive() override;

	// Carクラス継承により不要
//private:
//	std::unique_ptr<Engine> engine_; // 基底クラスを持たせる
};

/////////////////////////////////////////////////////////////////
// ElectricCar.cpp
ElectricCar::ElectricCar()
	: Car(std::make_unique<ElectricEngine>())
{}

void ElectricCar::drive()
{
}


/////////////////////////////////////////////////////////////////
// G28 問題点のある例
#if 0
	/////////////////////////////////////////////////////////////////
	// ElectricEngine.h
	class ElectricEngine
	{
	public:
		void start();
		void stop();

	private:
	};


	/////////////////////////////////////////////////////////////////
	// ElectricCar.h
	struct ElectricEngine;
	class ElectricCar
	{
	public:
		ElectricCar();

		void drive();

	private:
		//ElectricEngine engine_;
		std::unique_ptr<ElectricEngine> engine_;
	};

	ElectricCar::ElectricCar()
		: engine_{ std::make_unique<ElectricEngine>() }
	{
	}

	void ElectricCar::drive()
	{
	}
#endif


/////////////////////////////////////////////////////////////////
// Person.h
class Person
{
public:
	Person();
	~Person();

	Person(Person const& other);
	Person& operator=(Person const& other);

	Person(Person&& other);
	Person& operator=(Person&& other);

	int YearOfBirth() const;

private:
	struct Impl;
	std::unique_ptr<Impl> const pimpl_;
};

/////////////////////////////////////////////////////////////////
// Person.cpp
struct Person::Impl
{
	std::string foreName;
	std::string surName;
	std::string address;
	std::string city;
	std::string country;
	std::string zip;
	int yeayOfBirth;
};

Person::Person()
	: pimpl_{ std::make_unique<Impl>() }
{}
Person::~Person() = default;

Person::Person(Person const& other)
	: pimpl_{ std::make_unique<Impl>(*other.pimpl_) }
{}
Person& Person::operator=(Person const& other)
{
	*pimpl_ = std::move(*other.pimpl_);
	return *this;
}

Person::Person(Person&& other)
	: pimpl_{ std::make_unique<Impl>(std::move(*other.pimpl_)) }
{}
Person& Person::operator=(Person&& other)
{
	*pimpl_ = std::move(*other.pimpl_);
	return *this;
}

int Person::YearOfBirth() const
{
	return pimpl_->yeayOfBirth;
}

/////////////////////////////////////////////////////////////////
// strategyパターン例
class DatabaseEngine
{
public:
	virtual ~DatabaseEngine() = default;
};

class Database
{
public:
	explicit Database(std::unique_ptr<DatabaseEngine> engine);

private:
	std::unique_ptr<DatabaseEngine> engine_;
};

Database::Database(std::unique_ptr<DatabaseEngine> engine)
	: engine_{std::move(engine)}
{
}

/////////////////////////////////////////////////////////////////
// bridgeパターン例
class Database2
{
public:
	explicit Database2();

private:
	std::unique_ptr<DatabaseEngine> pimpl_;
};

class ConcreteDatabaseEngine : public DatabaseEngine
{
};

Database2::Database2()
	: pimpl_{std::make_unique<ConcreteDatabaseEngine>()}
{
}


NS_END

void Guideline28()
{
	CLASS_TITLE;
}

