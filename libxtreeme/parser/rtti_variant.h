#pragma once

#include <memory>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;

class Variant
{
	struct Base
	{
		virtual auto copy() -> unique_ptr<Base> = 0;
		virtual ~Base();
	};

	template <typename T>
	struct Typed: public Base
	{
		T value;

		Typed(T v): value(std::move(v)) {}

		auto copy() -> unique_ptr<Base> override
		{
			return make_unique<Typed>(value);
		}
	};

	std::unique_ptr<Base> ptr;

public:
	Variant() {}

	template <typename T>
	Variant(T t): ptr{std::make_unique<Typed<T>>(std::move(t))} {}

	Variant(const Variant& other): ptr(other ? other.ptr->copy() : 0) {}
	Variant(Variant&& other): ptr(std::move(other.ptr)) {}

	template <typename T>
	Variant& operator=(T t) { ptr = std::make_unique<Typed<T>>(std::move(t)); }

	Variant& operator=(const Variant& other) { ptr = other ? other.ptr->copy() : 0; }
	Variant& operator=(Variant&& other) { ptr = std::move(other.ptr); }

	operator bool() const { return (bool) ptr; }

	template <typename T>
	auto get() -> optional<T>
	{
		auto v = dynamic_cast<Typed<T>*>(&*ptr);
		if (v)
			return v->value;
		else
			return {};
	}
};
