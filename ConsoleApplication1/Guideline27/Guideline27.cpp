#include <vector>
#include <string>
#include <numeric>
#include <iosfwd>
#include <iterator>
#include <array>
#include <utility>
#include <cstdlib>

#define GUIDELINE_NAME "Guideline27"
#define NS_GUIDELINE_START namespace G27 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Addable.h
template<typename Derived>
struct Addable
{
	friend Derived& operator+=(Derived& lhs, Derived const& rhs)
	{
		lhs.get() += rhs.get();
	}

	friend Derived operator+(Derived const& lhs, Derived const& rhs)
	{
		return Derived{ lhs.get() + rhs.get() };
	}
};

/////////////////////////////////////////////////////////////////
// Printable.h
template<typename Derived>
struct Printable
{
	friend std::ostream& operator<<(std::ostream& os, const Derived& d)
	{
		os << d.get();
		return os;
	}
};

/////////////////////////////////////////////////////////////////
// Swappable.h
template<typename Deived>
struct Swappable
{
	friend void swap(Derived& lhs, Derived& rhs)
	{
		using std::swap;
		swap(lhs.get(), rhs.get());
	}
};

/////////////////////////////////////////////////////////////////
// StrongType.h
template<typename T, typename Tag>
struct StrongType : private Addable<StrongType<T, Tag>>
{
public:
	using value_typ = T;

	explicit StrongType(T const& value) : value_(value) {}

	T& get() { return value_; }
	T const& get() const { return value_; }

private:
	T value_;
};

/////////////////////////////////////////////////////////////////
// Distances.h
template<typename T>
using Meter =
	StrongType<T, struct MeterTag, Addable, Printable, Swappable>;

template<typename T>
using Kilometer =
	StrongType<T, struct KilometerTag, Addable, Printable, Swappable>;

/////////////////////////////////////////////////////////////////
// Person.h
using Surname =	
	StrongType<std::string, struct SurnameTag, Printable, Swappable>;



NS_END

void Guideline27()
{
	CLASS_TITLE;

	auto const m1 = G27::Meter<long>{ 120L };
	auto const m2 = G27::Meter<long>{ 50L };
	auto const km = G27::Kilometer<long>{ 30L };
	auto const surname1 = G27::Surname{ "Stroustrup" };
	auto const surname2 = G27::Surname{ "Iglberger" };

	auto const m3 = m1 + m2;
	//m1 + km;
	//surname1 + surname2;
	//m1 + m2;

}
