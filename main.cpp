#include <vector>
#include <iostream>
#include "vector/vector.hpp"
#include <cstring>
#include "type_traits.hpp"

int main()
{
    ft::vector<int> a1;
    std::vector<int> a2;

    for (int i = 1; i < 200; ++i)
        a1.insert(a1.end(), i);
    for (int i = 0; i < 200; ++i)
        std::cout << a1[i] << " ";
    std::cout << std::endl << a1.size() << " " << a1.capacity() << std::endl;


    return 0;
}