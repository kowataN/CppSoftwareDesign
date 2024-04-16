#include <memory>
#include <vector>
#include <string>
#include <set>
#include <funtinal.h>

#define GUIDELINE_NAME "Guideline25"
#define NS_GUIDELINE_START namespace G25 {
#define NS_END }
#include <iostream>
#include <format>
#define CLASS_TITLE std::cout << std::format("\n {:-^25} \n", GUIDELINE_NAME)

NS_GUIDELINE_START

/////////////////////////////////////////////////////////////////
// Observer.h

// 基本的な形（プッシュオブザーバ）
/*
class Observer
{
public:
	virtual ~Observer() = default;
	virtual void update() = 0;
};
*/

// サブジェクトの参照を渡す形（プルオブザーバ）
/*
class Subject;
class Observer
{
public:
	virtual ~Observer() = default;
	virtual void update(Subject const& subject) = 0;
};
*/

// テンプレートを使った例
/*
template<typename Subject, typename StateTag>
class Observer
{
class:
	virtual ~Observer() = default;

	virtual void udpate(Subject const& subject, StateTag Property) = 0;
};
*/

/////////////////////////////////////////////////////////////////
// Person.h
class Person
{
public:
	enum StateChange
	{
		forenameChanged,
		surnameChanged,
		addressChanged,
	};

	using PsersonObserver = Observer<Person, StateChange>;

	explicit Person(std::string forename, std::string surname)
		: forename_{ std::move(forename) }
		, surname_{ std::move(surname) }
	{}

	bool attach(PsersonObserver* observer);
	bool detach(PsersonObserver* observer);

	void notify(StateChange property);

	void forename(std::string newForename);
	void surname(std::string newSurname);
	void address(std::string newAddress);

	std::string const& forename() const { return forename_; }
	std::string const& surname() const { return surname_; }
	std::string const& address() const { return address_; }

private:
	std::string forename_;
	std::string surname_;
	std::string address_;

	std::set<PsersonObserver*> observers_;
};

bool Person::attach(PsersonObserver* observer)
{
	auto [pos, success] = observers_.insert(observer);
	return success;
}

bool Person::detach(PsersonObserver* observer)
{
	return (observers_.erase(observer) > 0U);
}

void Person::notify(StateChange property)
{
	for (auto iter=begin(observers_); iter!=end(observers_);)
	{
		auto const pos = iter++;
		(*pos)->udpate(*this, property);
	}
}

void Person::forename(std::string newForename)
{
	forename_ = newForename;
	notify(forenameChanged);
}

void Person::surname(std::string newSurname)
{
	surname_ = newSurname;
	notify(surnameChanged);
}

void Person::address(std::string newAddress)
{
	address_ = newAddress;
	notify(addressChanged);
}

/////////////////////////////////////////////////////////////////
// NameObserver.h
class NameObserver : Observer<Person, Person::StateChange>
{
public:
	void update(Person const& person, Person::StateChange property) override;
};

void NameObserver::update(Person const& person, Person::StateChange property)
{
	if (property == Person::forenameChanged ||
		property == Person::surnameChanged)
	{
		// 何らかの処理
	}
}

/////////////////////////////////////////////////////////////////
// AddressObserver
class AddressObserver : Observer<Person, Person::StateChange>
{
public:
	void update(Person const& person, Person::StateChange property) override;
};

void AddressObserver::update(Person const& person, Person::StateChange property)
{
	if (property == Person::addressChanged)
	{
		// 何らかの処理
	}
}

/////////////////////////////////////////////////////////////////
// Observer.h

// std::functionの例
template<typename Subject, typename StateTag>
class Observer
{
public:
	using OnUpdate = std::function<void(Subject const&, StateTag)>;

	explicit Observer(OnUpdate onUpdate) : onUpdate_{std::move(onUpdate)};

	void update(Subject const& subject, StateTag property)
	{
		onUpdate_(subject, property);
	}

private:
	OnUpdate onUpdate_;
};

void propertyChanged(Person const& person, Person::StateChange property)
{
	if (property == Person::forenameChanged ||
		property == Person::surnameChanged)
	{
	}
}

NS_END

void Guideline25()
{
	CLASS_TITLE;

/* // テンプレートの例
	G25::NameObserver nameObserver;
	G25::AddressObserver addressObserver;

	G25::Person homer("Homer",	"Simpson");
	G25::Person marge("Marge",	"Simpson");
	G25::Person monty("Monty",	"Burns");

	// attach
	homer.attach(&nameObserver);
	marge.attach(&addressObserver);
	monty.attach(&addressObserver);

	homer.forename("Homer Jay");

	marge.address("712 Red Bark");

	monty.address("Springfield");

	homer.detach(&nameObserver);
*/ // テンプレートの例

	// std::functionの例
	using PersonObserver = G25::Observer<G25::Person, G25::Person::StateChange>;

	PersonObserver nameObserver(G25::propertyChanged);

	PersonObserver addressObserver(
		[](G25::Person const& person, G25::Person::StateChange property)
		{
			if (property == G25::Person::addressChanged)
			{
				// アドレス変更
			}
		}
	);

	G25::Person homer("Homer", "Simpson");
	G25::Person marge("Marge", "Simpson");
	G25::Person monty("Monty", "Burns");
	// attach
	homer.attach(&nameObserver);
	marge.attach(&addressObserver);
	monty.attach(&addressObserver);
}

