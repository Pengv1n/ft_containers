#include <gtest/gtest.h>
#include "set.hpp"
#include <set>
#include <iostream>

class IntSet100 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        data = new ft::set<int>;
        for (int i = 0; i < S; ++i) {
            data->insert(i);
        }
    }

    void TearDown() override
    {
        delete data;
    }

    const   int S = 100;
    ft::set<int>  *data{};
};

TEST(CONSTRUCT, default_con) {
    ft::set<int>    a;
    std::set<int>   b;
    ft::set<int>::iterator  i = a.begin();
    std::set<int>::iterator  j = b.begin();

    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
    while (i != a.end()) {
        EXPECT_EQ(*i, *j);
    }
}

TEST_F(IntSet100, iterator_con) {
    ft::set<int>    b(data->begin(), data->end());

    ft::set<int>::iterator  i = data->begin();
    ft::set<int>::iterator  j = b.begin();
    EXPECT_EQ(data->size(), b.size());
    EXPECT_EQ(data->empty(), b.empty());
    while (i != data->end()) {
        EXPECT_EQ(*i, *j);
        ++i;
        ++j;
    }
}

TEST_F(IntSet100, copy_con) {
    ft::set<int>    b(*data);

    ft::set<int>::iterator  i = data->begin();
    ft::set<int>::iterator  j = b.begin();
    EXPECT_EQ(data->size(), b.size());
    EXPECT_EQ(data->empty(), b.empty());
    while (i != data->end()) {
        EXPECT_EQ(*i, *j);
        ++i;
        ++j;
    }
}

TEST_F(IntSet100, operator_assign) {
    ft::set<int>    b;
    b = *data;

    ft::set<int>::iterator  i = data->begin();
    ft::set<int>::iterator  j = b.begin();
    EXPECT_EQ(data->size(), b.size());
    EXPECT_EQ(data->empty(), b.empty());
    while (i != data->end()) {
        EXPECT_EQ(*i, *j);
        ++i;
        ++j;
    }
}

TEST_F(IntSet100, rev_iterator) {
    ft::set<int>::reverse_iterator i = data->rbegin();
    int k = S;

    while (i != data->rend()) {
        --k;
        EXPECT_EQ(*i, k);
        ++i;
    }
}

TEST(MODIFIERS, clear) {
    ft::set<int>    a;

    for (int i = 0; i < 1000; ++i)
        a.insert(std::rand());

    a.clear();

    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.empty(), true);
}

TEST(MODIFIERS, insert_pos) {
    ft::set<int>    a;
    const int S = 100;

    for (int i = 0; i < S; ++i) {
        a.insert(a.end(), i);
    }

    ft::set<int>::iterator k = a.begin();
    EXPECT_EQ(a.size(), S);
    EXPECT_EQ(a.empty(), false);
    int i = 0;
    while (k != a.end()) {
        EXPECT_EQ(*k, i++);
        ++k;
    }
}

TEST(MODIFIERS, insert_iterators) {
    ft::set<int>    a;
    const int S = 100;

    for (int i = 0; i < S; ++i) {
        a.insert(a.end(), i);
    }

    ft::set<int>    b(a.begin(), a.end());
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a == b, true);
}

TEST_F(IntSet100, erase_pos) {
    int i = S;

    while (data->size()) {
        data->erase(data->begin());
        --i;
        EXPECT_EQ(data->size(), i);
    }

    EXPECT_EQ(data->empty(), true);
}

TEST_F(IntSet100, erase_iterators) {
    data->erase(data->begin(), data->end());

    EXPECT_EQ(data->size(), 0);
    EXPECT_EQ(data->empty(), true);
}

TEST_F(IntSet100, erase_key) {
    int i = S;
    while (--i >= 0) {
        data->erase(i);
        EXPECT_EQ(data->size(), i);
    }

    EXPECT_EQ(data->empty(), true);
}

//TEST(RANDOM_INSERT_DELETE, test) {
//    std::vector<int>    tmp;
//    ft::set<int>    a;
//    int i = -1;
//    const int N = 10;
//
//    while (++i < N) {
//        int k = std::rand();
//        a.insert(k);
//        tmp.push_back(k);
//    }
//
//    EXPECT_EQ(a.size(), N);
//
//    i = N;
//    while (--i > 0) {
//        int s = static_cast<int>(tmp.size()) / 2;
//        a.erase(tmp[s]);
//        tmp.erase(tmp.begin() + s);
//        EXPECT_EQ(a.size(), i);
//    }
//
//}

TEST_F(IntSet100, count) {
    for (int i = 0; i < 2*S; ++i) {
        EXPECT_EQ(static_cast<bool>(data->count(i)), i < S);
    }
}

TEST_F(IntSet100, lower_bound) {
    EXPECT_EQ(*(data->lower_bound(57)), 57);
    EXPECT_EQ(*(data->lower_bound(-1)), 0);
    EXPECT_EQ(data->lower_bound(100), data->end());
    EXPECT_EQ(data->lower_bound(102), data->end());

    data->erase(57);
    EXPECT_EQ(*(data->lower_bound(57)), 58);
}

TEST_F(IntSet100, upper_bound) {
    EXPECT_EQ(*(data->upper_bound(57)), 58);
    EXPECT_EQ(*(data->upper_bound(-1)), 0);
    EXPECT_EQ(data->upper_bound(100), data->end());
    EXPECT_EQ(data->upper_bound(102), data->end());

    data->erase(57);
    EXPECT_EQ(*(data->upper_bound(57)), 58);
    EXPECT_EQ(*(data->upper_bound(56)), 58);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}