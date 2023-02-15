#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
    ft::vector<int> a;

//    std::vector<int> b;
    for (int i = 0; i < 100; ++i) {
        a.resize(i);
        for (int j = 0; j < a.size(); ++j)
            std::cout << a[j] << " ";
        std::cout << "\n";
    }
    return 0;
}