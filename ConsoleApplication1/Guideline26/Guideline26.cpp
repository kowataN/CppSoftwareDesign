#include <vector>
#include <string>
#include <numeric>
#include <iosfwd>
#include <iterator>
#include <array>

#define GUIDELINE_NAME "Guideline26"
#define NS_GUIDELINE_START namespace G26 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// DynamincVector.h
template<typename T>
class DynamicVector
{
public:
	using value_trype = T;
	using iterator = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;

	size_t size() const;

	T& operator[](size_t index);
	T const& operator[](size_t index) const;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

private:
	std::vector<T> values_;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, DynamicVector<T> const& vector)
{
	os << "(";
	for (auto const& element : vector)
	{
		os << " " << element;
	}
	os << " )";

	return os;
}

template<typename T>
auto l2norm(DynamicVector<T> const& vector)
{
	using std::begin, std::end;
	return std::sqrt(std::inner_product(begin(vector), end(vector), begin(vector), T{}));
}

/////////////////////////////////////////////////////////////////
// StaticVector.h
template<typename T, size_t Size>
class StaticVector
{
public:
	using vale_type = T;
	using iterator = typename std::array<T, Size>::iterator;
	using const_iterator = typename std::array<T, Size>::const_iterator;

	size_t size() const;

	T& operator[](size_t index);
	T const& operator[](size_t index) const;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

private:
	std::array<T, Size> values_;
};

template<typename T, size_t Size>
std::ostream& operator<<(std::ostream& os, StaticVector<T, Size> const& vector)
{
	os << "(";
	for (auto const& element : vector)
	{
		os << " " << element;
	}
	os << " )";
}

template<typename T, size_t Size>
auto l2norm(StaticVector<T, Size> const& vector)
{
	using std::begin,std::end;
	return std::sqrt(std::inner_product(begin(vector), end(vector), begin(vector), T{}));
}

/////////////////////////////////////////////////////////////////
// DenseVector.h
//template<typename T>
//class DenseVector
//{
//public:
//	virtual ~DenseVector() = default;
//
//	virtual size_t size() const = 0;
//
//	virtual T& operator[](size_t index) = 0;
//	virtual T const& operator[](size_t index) const = 0;
//};

template<typename Derived>
struct DenseVector
{
protected:
	// 仮想関数を排除するため、非仮想関数として実装
	~DenseVector() = default;

public:
	Derived& derived() { return static_cast<Derived&>(*this); }
	Derived const& derived() const { return static_cast<Derived const&>(*this); }

	size_t size() const { return derived().size(); }

	using value_type = typename Derived::value_type;
	using iterator = typename Derived::iterator;
	using const_iterator = typename Derived::const_iterator;

	value_type& operator[](size_t index) { return derived()[index]; }
	value_type const& operator[](size_t index) const { return derived()[index]; }

	iterator begin() { return derived().begin(); }
	const_iterator begin() const { return derived().begin(); }

	iterator end() { return derived().end(); }
	const_iterator end() const { return derived().end(); }
};

template<typename T, size_t Size>
std::ostream& operator<<(std::ostream& os, DenseVector<T> const& vector)
{
	os << "(";
	for (auto const& element : vector)
	{
		os << " " << element;
	}
	os << " )";
}

NS_END

void Guideline26()
{
	CLASS_TITLE;

}

