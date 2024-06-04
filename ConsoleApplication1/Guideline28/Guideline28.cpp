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

	virtual void statr() = 0;
	virtual void end() = 0;

private:
};

/////////////////////////////////////////////////////////////////
// ElectricCar.h
class ElectricCar
{
public:
	void drive();

private:
	std::unique_ptr<Engine> engine_; // 基底クラスを持たせる
};

/////////////////////////////////////////////////////////////////
// ElectricEngine.h
class ElectricEngine : public Engine
{
public:
	virtual void statr() override;
	virtual void end() override;
};

/////////////////////////////////////////////////////////////////
// ElectricCar.cpp
ElectricCar::ElectricCar()
	: engine_{ std::make_unique<ElectricEngine>() }
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


NS_END

void Guideline28()
{
	CLASS_TITLE;
}
