#include "catch2/catch_all.hpp"
#include "SSEngine/Memory/StackMemPool.hpp"
#include "SSEngine/Memory.hpp"
using namespace SSEngine;

TEST_CASE("StackMemPool")
{
    constexpr sizet poolSize = sizeof(int) * 100;
    StackMemPool<poolSize> pool;
}