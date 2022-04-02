#include "test.h"
#include <iostream>

using namespace std;

// A function with a global name
int sqr(int n)
{
    return n * n;
}

int main()
{
    cout << "The square of 3 is " << sqr(3) << endl;
    return 0;
}
