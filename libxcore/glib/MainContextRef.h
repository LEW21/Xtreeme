#ifndef X_MainContextRef_h
#define X_MainContextRef_h

#include <glib.h>

namespace X
{
	struct MainContextRef
	{
		GMainContext* context;
		enum DefaultType {Default};
		enum NewType {New};

		inline MainContextRef(GMainContext* ctx = 0);
		inline MainContextRef(DefaultType);
		inline MainContextRef(NewType);

		inline MainContextRef(const MainContextRef& other);
		inline MainContextRef(MainContextRef&& other);

		inline ~MainContextRef();

		inline MainContextRef& operator=(GMainContext* ctx);

		inline MainContextRef& operator=(const MainContextRef& other);
		inline MainContextRef& operator=(MainContextRef&& other);

		inline operator GMainContext*() const {return context;}
		inline bool isValid() const {return context;}
	};

	inline MainContextRef::MainContextRef(GMainContext* ctx)
		: context(ctx)
	{
		if (context)
			g_main_context_ref(context);
	}

	inline MainContextRef::MainContextRef(DefaultType)
		: context(g_main_context_get_thread_default())
	{
		if (!context)
			context = g_main_context_default();
		if (context)
			g_main_context_ref(context);
	}

	inline MainContextRef::MainContextRef(NewType)
		: context(g_main_context_new())
	{}

	inline MainContextRef::~MainContextRef()
	{
		if (context)
			g_main_context_unref(context);
	}

	inline MainContextRef::MainContextRef(const MainContextRef& other)
		: context(other.context)
	{
		if (context)
			g_main_context_ref(context);
	}

	inline MainContextRef::MainContextRef(MainContextRef&& other)
		: context(other.context)
	{
		other.context = 0;
	}

	inline MainContextRef& MainContextRef::operator=(GMainContext* other)
	{
		if (other)
			g_main_context_ref(other);

		if (context)
			g_main_context_unref(context);

		context = other;

		return *this;
	}
	
	inline MainContextRef& MainContextRef::operator=(const MainContextRef& other)
	{
		*this = other.context;

		return *this;
	}

	inline MainContextRef& MainContextRef::operator=(MainContextRef&& other)
	{
		std::swap(context, other.context);
		other = 0;

		return *this;
	}
}

namespace std
{
	template <>
	inline void swap(X::MainContextRef& first, X::MainContextRef& second)
	{
		swap(first.context, second.context);
	}
}

#endif
