#include "catch2/catch_all.hpp"
#include "AtomEngine/Invokable/InvokableBox.hpp"
#include "AtomEngine/Invokable/InvokableImpl.hpp"

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

TEST_CASE("InvokableBox", "[Implementation]")
{
    using IInvokableT = IInvokable<int(int, char, uint)>;
    using InvokableMakerT = TInvokableMaker<int(int, char, uint)>;
    using InvokableBoxT = InvokableBox<int(int, char, uint)>;

    InvokableBoxT function = InvokableMakerT::Make(& testFunc);
    InvokableBoxT functor = InvokableMakerT::Make(Functor());
    InvokableBoxT lambda = InvokableMakerT::Make(
        [](int a, char b, uint c)
        {
            return 2;
        });

    InvokableBoxT capturedLambda = InvokableMakerT::Make(
        [&](int a, char b, uint c)
        {
            return 3;
        });

    InvokableBoxT functionCopy = function;

    InvokableBoxT functionCopyByOperator;
    functionCopyByOperator = function;

    CHECK(function->Invoke(0, 'a', 0) == 0);
    CHECK(functor->Invoke(0, 'a', 0) == 1);
    CHECK(lambda->Invoke(0, 'a', 0) == 2);
    CHECK(capturedLambda->Invoke(0, 'a', 0) == 3);
}