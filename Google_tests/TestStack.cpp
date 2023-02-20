#include "gtest/gtest.h"
#include "stack.hpp"

class DefaultIntStack : public ::testing::Test
{
protected:
    void SetUp() override
    {
        data = new ft::stack<int>;
    }

    void TearDown() override
    {
        delete data;
    }

    const   int S = 100;
    ft::stack<int>  *data{};
};

class Int100Stack : public ::testing::Test
{
protected:
    void SetUp() override
    {
        data = new ft::stack<int>;
        int i = -1;
        while (++i < S)
            data->push(i);
    }

    void TearDown() override
    {
        delete data;
    }

    const   int S = 100;
    ft::stack<int>  *data{};
};

TEST_F(DefaultIntStack, test1)
{
    EXPECT_EQ(data->size(), 0);
    EXPECT_EQ(data->empty(), true);

    for (int i = 0; i < S; ++i)
    {
        EXPECT_EQ(data->size(), i);
        data->push(i);
    }
}

TEST_F(Int100Stack, test1)
{
    EXPECT_EQ(data->size(), S);
    EXPECT_EQ(data->empty(), false);
    EXPECT_EQ(data->top(), S-1);

    for (int i = S; i > 0; --i)
    {
        EXPECT_EQ(data->top(), i - 1);
        data->pop();
        EXPECT_EQ(data->size(), i - 1);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}