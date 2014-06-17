#ifndef X_Variant_h
#define X_Variant_h

#include "CoreType.h"

namespace X
{
	struct Variant
	{
		TypeID type;
		Word value;

		inline Variant();

		template <class T>
		inline Variant(T&& v);

		inline Variant(const Variant& other);
		inline Variant(Variant& other);
		inline Variant(Variant&& other);

		template <class T>
		inline Variant& operator=(T&& v);

		inline Variant& operator=(const Variant& other);
		inline Variant& operator=(Variant& other);
		inline Variant& operator=(Variant&& other);

		inline bool isValid() const;

		template <class T> inline bool is() const;
		template <class T> inline T as() const;
		template <class T> inline operator T() const;

		inline bool operator==(const Variant& other) const;
		inline bool operator!=(const Variant& other) const;

		inline ~Variant();
	};

	inline Variant::Variant()
		: type(0)
		, value(0)
	{}

	template <class T>
	inline Variant::Variant(T&& v)
		: type(typeOf<typename std::remove_const<typename std::remove_reference<T>::type>::type>::type)
		, value(0)
	{
		coreTypes[type]->construct(&value, Unit::create<typename std::remove_const<typename std::remove_reference<T>::type>::type>(std::forward<T>(v)));
	}

	inline Variant::Variant(const Variant& other)
		: type(other.type)
		, value(0)
	{
		if (type)
			coreTypes[type]->construct(&value, other.value);
	}

	inline Variant::Variant(Variant& other)
		: type(other.type)
		, value(0)
	{
		if (type)
			coreTypes[type]->construct(&value, other.value);
	}

	inline Variant::Variant(Variant&& other)
		: type(other.type)
		, value(0)
	{
		if (type)
			coreTypes[type]->construct(&value, std::move(other.value));
	}

	template <class T>
	inline Variant& Variant::operator=(T&& v)
	{
		if (type)
		{
			if (type == typeOf<typename std::remove_reference<T>::type>::type)
			{
				coreTypes[type]->set(&value, Unit::create(std::forward<typename std::remove_reference<T>::type>(v)));
				return *this;
			}

			coreTypes[type]->destruct(&value);
		}
		type = typeOf<typename std::remove_reference<T>::type>::type;
		coreTypes[type]->construct(&value, Unit::create(std::forward<typename std::remove_reference<T>::type>(v)));

		return *this;
	}

	inline Variant& Variant::operator=(const Variant& other)
	{
		if (type)
		{
			if (type == other.type)
			{
				coreTypes[type]->set(&value, other.value);
				return *this;
			}

			coreTypes[type]->destruct(&value);
		}
		type = other.type;
		if (type)
			coreTypes[type]->construct(&value, other.value);

		return *this;
	}

	inline Variant& Variant::operator=(Variant& other)
	{
		return operator=(const_cast<const Variant&>(other));
	}

	inline Variant& Variant::operator=(Variant&& other)
	{
		if (type)
		{
			if (type == other.type)
			{
				coreTypes[type]->set(&value, std::move(other.value));
				return *this;
			}

			coreTypes[type]->destruct(&value);
		}
		type = other.type;
		if (type)
			coreTypes[type]->construct(&value, std::move(other.value));

		return *this;
	}

	inline bool Variant::isValid() const
	{
		return type;
	}

	template <class T> inline bool Variant::is() const
	{
		return type == typeOf<T>::type;
	}

	template <class T> inline T Variant::as() const
	{
		return word_cast<T>(value);
	}

	template <class T> inline Variant::operator T() const
	{
		return as<T>();
	}

	inline bool Variant::operator==(const Variant& other) const
	{
		return type == other.type && (!type || coreTypes[type]->compare(value, other.value));
	}

	inline bool Variant::operator!=(const Variant& other) const
	{
		return !operator==(other);
	}

	inline Variant::~Variant()
	{
		if (type)
			coreTypes[type]->destruct(&value);
	}
}

namespace std
{
	template<>
	struct hash<X::Variant>
	{
		size_t operator()(const X::Variant& v) const
		{
			if (v.type)
				return X::coreTypes[v.type]->hash(v.value);
			else
				return 0;
		}
	};
}

#endif
