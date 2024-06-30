#include <vector>
#include <memory>
#include <string>
#include <numeric>
#include <iosfwd>
#include <iterator>
#include <array>
#include <utility>
#include <cstdlib>
#include <variant>

#define GUIDELINE_NAME "Guideline30"
#define NS_GUIDELINE_START namespace G30 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Animal.h
class Animal
{
public:
	virtual ~Animal() = default;
	virtual void makeSound() const = 0;
	virtual std::unique_ptr<Animal> clone() const = 0; // プロトタイプパターン
};

/////////////////////////////////////////////////////////////////
// Sheep.h
class Sheep : public Animal
{
public:
	explicit Sheep(std::string name) : name_{std::move(name)} {}

	void makeSound() const override;
	std::unique_ptr<Animal> clone() const override; // プロトタイプパターン

private:
	std::string name_;
};

void Sheep::makeSound() const
{
	std::cout << "baa\n";
}

std::unique_ptr<Animal> Sheep::clone() const
{
	return std::make_unique<Sheep>(*this); // Sheepをコピー
}

/////////////////////////////////////////////////////////////////
// variant
class Dog {};
class Cat {};
class Sheep2 {};

NS_END

void Guideline30()
{
	CLASS_TITLE;

	std::unique_ptr<G30::Animal> const dolly = std::make_unique<G30::Sheep>("Dolly");
	std::unique_ptr<G30::Animal> dollyClone = dolly->clone();

	dolly->makeSound();
	dollyClone->makeSound();

	std::variant<G30::Dog, G30::Cat, G30::Sheep2> animal1{};
	auto animal2 = animal1; // Animal1のコピーを作成

}

