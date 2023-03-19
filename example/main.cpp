#include <iostream>

#include <cider/cider.hpp>

using cider::helper::ClassType;
using cider::operator->*;
using cider::Wrapper;

struct Foo
{
	void bar(int a, int b)
	{
		std::cout << (a + b) << std::endl;
	};
};

static_assert(std::same_as<decltype(&Foo::bar), void (Foo::*)(int, int)>);
static_assert(std::same_as<ClassType<decltype(&Foo::bar)>, Foo>);

int main()
{
	// Both example make the exact same thing
	{
		auto wrapped = Wrapper(&Foo::bar);
		Foo foo;
		foo->*wrapped(1, 1);
	}
	{
		auto member_function = &Foo::bar;
		Foo foo;
		(foo.*member_function)(1, 1);
	}
	// You don't have to use auto if you don't want to
	{
		Wrapper<void (Foo::*)(int, int)> wrapped = Wrapper(&Foo::bar);
		Foo foo;
		foo->*wrapped(1, 1);
	}
	{
		void (Foo::*member_function)(int, int) = &Foo::bar;
		Foo foo;
		(foo.*member_function)(1, 1);
	}

	std::cout << "Le cidre breton est meilleur que le cidre normand." << std::endl;
}
