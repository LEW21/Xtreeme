#ifndef X_Types_h
#define X_Types_h

#include <cstddef>
#include <cstdint>

namespace X
{
	typedef unsigned int uint;

	typedef uint64_t U64;
	typedef int64_t  S64;

	typedef uint32_t U32;
	typedef int32_t  S32;

	typedef uint16_t U16;
	typedef int16_t  S16;

	typedef uint8_t  U8;
	typedef int8_t   S8;

	typedef char     Byte;
	typedef char     UTF8Char;
	typedef char16_t UTF16Char;
	typedef char32_t UTF32Char;

	typedef std::size_t Size;
}

#endif
