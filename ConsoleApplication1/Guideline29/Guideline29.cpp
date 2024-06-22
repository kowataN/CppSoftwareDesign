#include <vector>
#include <memory>
#include <string>
#include <numeric>
#include <iosfwd>
#include <iterator>
#include <array>
#include <utility>
#include <cstdlib>

#define GUIDELINE_NAME "Guideline29"
#define NS_GUIDELINE_START namespace G29 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Person1.h
class Person1
{
public:
	virtual ~Person1() = default;

private:
	std::string foreName;
	std::string surName;
	std::string address;
	std::string city;
	std::string country;
	std::string zip;
	int yeayOfBirth;
};

/////////////////////////////////////////////////////////////////
// Person2.h
class Person2
{
public:
	explicit Person2();
	~Person2();

private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};

struct Person2::Impl
{
	std::string foreName;
	std::string surName;
	std::string address;
	std::string city;
	std::string country;
	std::string zip;
	int yeayOfBirth;
};

Person2::Person2()
	: pimpl{std::make_unique<Impl>()}
{
}

Person2::~Person2()
{
}

/////////////////////////////////////////////////////////////////
// 
class Person3
{
public:
	explicit Person3();
	~Person3();

private:
private:
	std::string foreName;
	std::string surName;
	int yeayOfBirth;

	struct Impl;
	std::unique_ptr<Impl> pimpl;
};

struct Person3::Impl
{
	std::string address;
	std::string city;
	std::string country;
	std::string zip;
};

Person3::Person3()
	: foreName{""}
	, surName{""}
	, yeayOfBirth(0)
	, pimpl{ std::make_unique<Impl>() }
{
}

Person3::~Person3() = default;

NS_END

void Guideline29()
{
	CLASS_TITLE;

	printf("Person1 size=%d\n", sizeof(G29::Person1));
	printf("Person2 size=%d\n", sizeof(G29::Person2));
	printf("Person3 size=%d\n", sizeof(G29::Person3));
}

