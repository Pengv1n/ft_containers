#include <iostream>
#include "vector.hpp"
#include <vector>
#include <map>
#include "pair.hpp"
#include "rb_tree.hpp"

int main()
{

    ft::rb_tree<int>    a;
    a.insert(45);

    a.insert(56);
    a.insert(23);
    a.insert(1);
    a.insert(111);
    a.insert(65);
    a.prettyPrint();
    a.deleteNode(45);
    a.prettyPrint();

    return 0;
}