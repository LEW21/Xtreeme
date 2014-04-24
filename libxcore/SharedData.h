#ifndef X_SharedData_h
#define X_SharedData_h

#include "Shared.h"

#define X_E() auto p = this->p.editable();
#define X_P(P) P* p = static_cast<P*>(&(*this->p));
#define X_EP(P) P* p = static_cast<P*>(&(*this->p.editable()));

namespace X
{
	struct SharedData: public Shared
	{
		SharedData();
		SharedData(const SharedData&);
		SharedData(SharedData&&);

		virtual SharedData* copy() const = 0;
	};
}

#endif
