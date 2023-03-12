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
    ft::map<int, int>    a;

    a[45] = 34;

    std::cout << a.find(45).get_node()->get_key().second;
    return 0;
}