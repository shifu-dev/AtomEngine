#include <iostream>
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ArrayIterator.hpp"

using namespace std;
using namespace Atom;

int main()
{
    cout << "Size of ArrayIterator: " << sizeof(ArrayIterator<int>) << endl
        << "Size of Pointer: " << sizeof(int*) << endl
        << "Actual Size of ArrayIterator: " << sizeof(ArrayIterator<int>) - sizeof(int*)
        << endl;

    return 0;
}