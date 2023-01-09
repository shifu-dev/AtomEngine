#include "catch2/catch_all.hpp"
#include "AtomEngine/String/Internal/ConstStringImpl.hpp"

using namespace Atom;

template <typename CharT>
class ConstStringTester: public Internal::TConstStringImpl<CharT>
{
public:
    ConstStringTester(const CharT* str)
    {
        const CharT* it = str;
        while (*it != '\0') it++;

        this->_array = CCAST(CharT*, str);
        this->_count = it - str;
    }
};

TEST_CASE("ConstString Implementation")
{
    ConstStringTester<char> str = "Just a test string";

    str.Compare("hello", { .index = 0 });
    str.StartsWith("hello");
    str.EndsWith("hello");
    str.FindFirst("hello", { .offset = 5 });
    str.FindLast("hello", { .offset = 5 });
    str.Contains("hello");

    str.FindFirstAny("hello", { .offset = 5 });
    str.FindFirstNotAny("hello", { .offset = 5 });
    str.FindLastAny("hello", { .offset = 5 });
    str.FindLastNotAny("hello", { .offset = 5 });
}