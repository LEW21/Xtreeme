#ifndef Xtreeme_Memory_DataDispatcher_h
#define Xtreeme_Memory_DataDispatcher_h

#include <ATL/queue.h>
#include <libxcore/Signal.h>
#include "Data.h"

namespace Xtreeme
{
	namespace Memory
	{
		/*
		* All reads/writes on one level are started concurrently.
		* read
		* read
		* read
		* write
		* - read
		* - read
		* - write
		* - - read
		*
		* Setup phase:
		* 	To obtain a pointer to the data:
		* 		dispatcher->data->connect([](const Data::Pointer& data) {
		* 			handle data
		* 		});
		*
		* 	To make all next reads wait for this operation to finish:
		* 		dispatcher->push();
		*
		* Handling phase:
		* 	To start all waiting reads:
		* 		dispatcher->pop(modifiedCopyOfData);
		*/

		class DataDispatcher
		{
		public:
			X::SharedSignal<Data::Pointer>* data;

		private:
			ATL::Queue<X::SharedSignal<Data::Pointer>::Pointer> queue;

		public:
			inline DataDispatcher()
			{
				push();
			}

			inline void push()
			{
				queue.push(data = new X::SharedSignal<Data::Pointer>);
			}

			inline void pop(const Data::Pointer& data)
			{
				(*queue.pop())(data);
			}
		};
	}
}

#endif
