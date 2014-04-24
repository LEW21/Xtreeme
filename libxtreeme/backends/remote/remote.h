#ifndef Xtreeme_Remote_remote_h
#define Xtreeme_Remote_remote_h

#if defined(XTREEME_EXPORT_REMOTE)
#  define REMOTE_EXPORT Q_DECL_EXPORT
#else
#  define REMOTE_EXPORT Q_DECL_IMPORT
#endif

#define X_P(P) P* p = static_cast<P*>(&(*this->p));
#endif
