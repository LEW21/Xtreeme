#ifndef Xtreeme_libxtreeme_h
#define Xtreeme_libxtreeme_h

#include <QDebug>
#if defined(XTREEME_EXPORT_LIB)
#  define XTREEME_EXPORT Q_DECL_EXPORT
#else
#  define XTREEME_EXPORT Q_DECL_IMPORT
#endif

#include "private.h"

#endif
