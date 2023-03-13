#include <iostream>
#include "vector.hpp"
#include <vector>
#include <map>
#include "pair.hpp"
#include "rb_tree.hpp"
#include "rb_iterator.hpp"
#include "set.hpp"
#include <set>
#include "map.hpp"

int main()
{
    std::map<int, int>    a;

    for (int i = 0; i < 234; ++i)
        a.insert(std::pair<int ,int>(i, i));

    return 0;
}