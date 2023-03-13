#include "map.hpp"
#include "gtest/gtest.h"

class DefaultIntMap : public ::testing::Test
{
protected:
    void SetUp() override
    {
        data = new ft::map<int, int>;
    }

    void TearDown() override
    {
        delete data;
    }

    const   int S = 100;
    ft::map<int, int>  *data{};
};

class IntMap100 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        data = new ft::map<int, int>;
        for (int i = 0; i < S; ++i) {
            data->insert(ft::pair<int,int>(i, i));
        }
    }

    void TearDown() override
    {
        delete data;
    }

    const   int S = 100;
    ft::map<int, int>  *data{};
};


TEST_F(DefaultIntMap, def_test) {
    EXPECT_EQ(data->size(), 0);
    EXPECT_EQ(data->empty(), true);
}

TEST_F(IntMap100, default_test) {
    EXPECT_EQ(data->size(), S);
    EXPECT_EQ(data->empty(), false);
    ft::map<int, int>::iterator i = data->begin();
    for (int n = 0; n < S; ++n) {
        EXPECT_EQ((*i).first, n);
        EXPECT_EQ((*i).second, n);
        ++i;
    }
}

TEST_F(IntMap100, con_iterator) {
    ft::map<int, int>   b(data->begin(), data->end());

    EXPECT_EQ(data->size(), b.size());
    EXPECT_EQ(data->empty(), b.empty());
    ft::map<int, int>::iterator a_i = data->begin();
    ft::map<int, int>::iterator b_i = b.begin();
    while (a_i != data->end()) {
        EXPECT_EQ((*a_i).first, (*b_i).first);
        EXPECT_EQ((*a_i).second, (*b_i).second);
        ++a_i;
        ++b_i;
    }
}

TEST_F(IntMap100, con_copy) {
    ft::map<int, int>   b(*data);

    EXPECT_EQ(data->size(), b.size());
    EXPECT_EQ(data->empty(), b.empty());
    ft::map<int, int>::iterator a_i = data->begin();
    ft::map<int, int>::iterator b_i = b.begin();
    while (a_i != data->end()) {
        EXPECT_EQ((*a_i).first, (*b_i).first);
        EXPECT_EQ((*a_i).second, (*b_i).second);
        ++a_i;
        ++b_i;
    }
}

TEST_F(IntMap100, operator_assign) {
    ft::map<int, int>  b;
    const int N = S / 2;

    for (int i = N; i > 0; --i) {
        b.insert(ft::pair<int, int>(i, i));
    }
    EXPECT_EQ(b.size(), N);
    EXPECT_EQ(b.empty(), false);

    (*data) = b;

    EXPECT_EQ(data->size(), N);
    EXPECT_EQ(data->empty(), false);
    ft::map<int, int>::iterator i = data->begin();
    for (int n = 1; n <= N; ++n) {
        EXPECT_EQ((*i).first, n);
        EXPECT_EQ((*i).second, n);
        ++i;
    }
}

TEST_F(IntMap100, at) {
    EXPECT_EQ(data->at(1), 1);
    data->at(1) = 34;
    EXPECT_EQ(data->at(1), 34);

}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}