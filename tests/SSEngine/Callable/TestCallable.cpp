#pragma once
#include <iostream>
#include "catch2/catch_all.hpp"
#include "SSEngine/Callable/Callable.hpp"

using namespace SSEngine;

class Functor
{
    int operator()(int a, char b, uint c)
    {
        // std::cout << "Hi! I am functor()" << std::endl;
        return 1;
    }
};

int testFunc(int a, char b, uint c)
{
    // std::cout << "Hi! I am function()" << std::endl;
    return 1;
}

TEST_CASE("Callable")
{
    using CallableT = Callable<int(int, char, uint)>;

    const CallableT lref functionCallable = CallableT::Create(lref testFunc);

    const CallableT lref functorCallable = CallableT::Create(lref testFunc);

    const CallableT lref lambdaCallable = CallableT::Create(
        [](int a, char b, uint c)
        {
            // std::cout << "Hi! I am lambda()" << std::endl;
            return 1;
        }
    );

    const CallableT lref captureLambdaCallable = CallableT::Create(
        [&](int a, char b, uint c)
        {
            // std::cout << "Hi! I am captureLambda()" << std::endl;
            return 1;
        }
    );

    CHECK(functionCallable(0, 'a', 0) == 1);
    CHECK(functorCallable(0, 'a', 0) == 1);
    CHECK(lambdaCallable(0, 'a', 0) == 1);
    CHECK(captureLambdaCallable(0, 'a', 0) == 1);
}