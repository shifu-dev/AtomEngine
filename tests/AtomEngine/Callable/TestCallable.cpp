#include "catch2/catch_all.hpp"
#include "AtomEngine/Invokable/IInvokable.hpp"
#include "AtomEngine/Invokable/InvokableImpl.hpp"

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

TEST_CASE("Invokable")
{
    using IInvokableT = IInvokable<int(int, char, uint)>;
    using InvokableMakerT = TInvokableMaker<int(int, char, uint)>;

    IInvokableT&& functionInvokable = InvokableMakerT::Make(&testFunc);

    IInvokableT&& functorInvokable = InvokableMakerT::Make(&testFunc);

    IInvokableT&& lambdaInvokable = InvokableMakerT::Make(
        [](int a, char b, uint c)
        {
            // std::cout << "Hi! I am lambda()" << std::endl;
            return 1;
        }
    );

    IInvokableT&& captureLambdaInvokable = InvokableMakerT::Make(
        [&](int a, char b, uint c)
        {
            // std::cout << "Hi! I am captureLambda()" << std::endl;
            return 1;
        }
    );

    CHECK(functionInvokable(0, 'a', 0) == 1);
    CHECK(functorInvokable(0, 'a', 0) == 1);
    CHECK(lambdaInvokable(0, 'a', 0) == 1);
    CHECK(captureLambdaInvokable(0, 'a', 0) == 1);
}