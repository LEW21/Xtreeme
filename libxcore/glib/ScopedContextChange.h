#ifndef X_ScopedContextChange_h
#define X_ScopedContextChange_h

#include "MainContextRef.h"

namespace X
{
	struct ScopedContextChange
	{
		MainContextRef context;

		inline ScopedContextChange(const MainContextRef& ctx): context(ctx)
		{
			g_main_context_push_thread_default(context);
		}

		inline ~ScopedContextChange()
		{
			g_main_context_pop_thread_default(context);
		}
	};
}

#endif
