#include <iostream>
#include <algorithm>

int main()
{
    int a = 3;
    a = a + 3;
    for (int i = 0; i < a; i++)
        a = a + a;
    std::cout << a << std::endl;
    return 0;
}