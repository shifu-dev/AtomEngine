#include "catch2/catch_all.hpp"
#include "AtomEngine/Callable/CallableBox.hpp"

using namespace Atom;

class Functor
{
    public: int operator()(int a, char b, uint c) const
    {
        return 1;
    }
};

static int testFunc(int a, char b, uint c)
{
    return 0;
}

TEST_CASE("CallableBox", "[Implementation]")
{
    using ICallableT = ICallable<int(int, char, uint)>;
    using CallableBoxT = CallableBox<int(int, char, uint)>;

    CallableBoxT function = ICallableT::Create(& testFunc);
    CallableBoxT functor = ICallableT::Create(Functor());
    CallableBoxT lambda = ICallableT::Create(
        [](int a, char b, uint c)
        {
            return 2;
        });

    CallableBoxT capturedLambda = ICallableT::Create(
        [&](int a, char b, uint c)
        {
            return 3;
        });

    CallableBoxT functionCopy = function;

    CallableBoxT functionCopyByOperator;
    functionCopyByOperator = function;

    CHECK(function->Invoke(0, 'a', 0) == 0);
    CHECK(functor->Invoke(0, 'a', 0) == 1);
    CHECK(lambda->Invoke(0, 'a', 0) == 2);
    CHECK(capturedLambda->Invoke(0, 'a', 0) == 3);
}