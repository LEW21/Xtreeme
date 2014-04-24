#ifndef Xtreeme_private_h
#define Xtreeme_private_h

#define X_P(P) P* p = static_cast<P*>(&(*this->p));
#define X_EP(P) P* p = static_cast<P*>(&(*this->p.editable()));

typedef QLatin1String QS;
typedef QLatin1Char   QC;

#include <QMetaType>
#include <QVector>

namespace Xtreeme
{
	template <class T>
	struct RegisterMetatype
	{
		inline RegisterMetatype(const char* name)
		{
			qRegisterMetaType<T>(name);
			qRegisterMetaType<QVector<T>>((QS("QVector<") + name + QS(">")).toLatin1());
		}
	};
}

#define X_DEFINE_METATYPE(T, var) Xtreeme::RegisterMetatype<T> _defmetatype##var(#T);

#endif
