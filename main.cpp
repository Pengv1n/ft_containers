#include <iostream>
#include "vector.hpp"
#include <vector>
#include "stack/stack.hpp"

int main()
{
    ft::stack<int>  a;
    ft::stack<int>  b;

    std::cout << (a==b);

    return 0;
}