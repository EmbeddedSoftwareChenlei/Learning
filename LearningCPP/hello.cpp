#include <iostream>
using namespace std;
#include "hello.h"

/*class Circle
{
    private:
        int r; // 半径
    public:
        Circle(int val);
        double size(); // 面积计算
};*/

Circle::Circle(int val)
{
    r = val;
}

double Circle::size()
{
    return 3.14*r*r;
}
