#include "catch2/catch_all.hpp"
#include "AtomEngine/Memory/StackMemPool.hpp"

using namespace Atom;

TEST_CASE("StackMemPool")
{
    constexpr sizet poolSize = sizeof(int) * 100;
    StackMemPool<poolSize> pool;
}