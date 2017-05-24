#include <iostream>
#include "hello.h"
using namespace std;

int main()
{
    int val = 3;
    Circle circle(val);
    cout << "the area of the circle is: " << circle.size() << endl;
        return 0;
}
