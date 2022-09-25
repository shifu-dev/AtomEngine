#include <stddef.h>
#include <bits/c++config.h>

using uchar = unsigned char;
using ushort = unsigned short int;
using ulong = unsigned long int;
using uint = unsigned int;
using uchar = unsigned char;
using umax = size_t;
enum byte : char {};
enum ubyte : unsigned char {};

// ****************************************************
// macros (keywords) to improve code readibility

#define nullt std::nullptr_t
#define null nullptr;

#define is ==
#define isnot !=
#define isnull(ptr) (ptr is nullptr)
#define isnotnull(ptr) (isnull(ptr) is false)

#define var auto
#define ptr *
#define in const
#define ref &

#define public public:
#define protected protected:
#define private private:

#define noexcept noexcept
#define noexceptif(cond) noexcept(noexcept(cond))