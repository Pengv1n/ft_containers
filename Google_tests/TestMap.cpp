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
    for (int i = 0; i < S; ++i) {
        EXPECT_EQ(data->at(i), i);
    }
    EXPECT_EQ(data->size(), S);

    for (int i = 0; i < S; ++i) {
        data->at(i) = i + S;
        EXPECT_EQ(data->at(i), i + S);
    }
    EXPECT_EQ(data->size(), S);

    ft::map<int, int>::iterator iter = data->begin();
    for (int i = S; i < 2*S; ++i, ++iter) {
        EXPECT_EQ((*iter).first, i - S);
        EXPECT_EQ((*iter).second, i);
    }
    EXPECT_EQ(data->size(), S);

    EXPECT_THROW(data->at(S), std::out_of_range);
}

TEST_F(IntMap100, square_brackets) {
    for (int i = 0; i < S; ++i) {
        EXPECT_EQ((*data)[i], i);
    }
    EXPECT_EQ(data->size(), S);
    EXPECT_THROW(data->at(2 * S), std::out_of_range);
    EXPECT_EQ((*data)[2 * S], int());

    (*data)[2 * S] = 3*S;
    EXPECT_EQ((*data)[2*S], 3*S);
    EXPECT_EQ(data->size(), S + 1);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}