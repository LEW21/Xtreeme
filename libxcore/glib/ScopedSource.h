#ifndef X_ScopedSource_h
#define X_ScopedSource_h

#include <glib.h>
#include "MainContextRef.h"

namespace X
{
	struct ScopedSource
	{
		GSource* source;

		inline ScopedSource(GSource* src, const MainContextRef& ctx = MainContextRef::Default): source(src)
		{
			g_source_attach(source, ctx);
		}

		inline ~ScopedSource()
		{
			g_source_destroy(source);
			g_source_unref(source);
		}
	};
}

#endif
