#ifndef Xtreeme_Memory_memory_h
#define Xtreeme_Memory_memory_h

#if defined(XTREEME_EXPORT_MEMORY)
#  define MEMORY_EXPORT Q_DECL_EXPORT
#else
#  define MEMORY_EXPORT Q_DECL_IMPORT
#endif

#define X_P(P) P* p = static_cast<P*>(&(*this->p));
#endif
