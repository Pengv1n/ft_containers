#include "gtest/gtest.h"
#include "rb_tree.hpp"

TEST(TEST_RB, test1) {
    ft::rb_tree<int>    a;
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}