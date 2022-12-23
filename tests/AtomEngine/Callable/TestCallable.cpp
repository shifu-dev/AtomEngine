#include "catch2/catch_all.hpp"
#include "AtomEngine/Callable/ICallable.hpp"

using namespace Atom;

class Functor
{
    int operator()(int a, char b, uint c)
    {
        // std::cout << "Hi! I am functor()" << std::endl;
        return 1;
    }
};

static int testFunc(int a, char b, uint c)
{
    // std::cout << "Hi! I am function()" << std::endl;
    return 1;
}

TEST_CASE("Callable")
{
    using ICallableT = ICallable<int(int, char, uint)>;

    const ICallableT& functionCallable = ICallableT::Create(&testFunc);

    const ICallableT& functorCallable = ICallableT::Create(&testFunc);

    const ICallableT& lambdaCallable = ICallableT::Create(
        [](int a, char b, uint c)
        {
            // std::cout << "Hi! I am lambda()" << std::endl;
            return 1;
        }
    );

    const ICallableT& captureLambdaCallable = ICallableT::Create(
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