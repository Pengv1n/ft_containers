#include <gtest/gtest.h>
#include "defs.hpp"
#include "vector.hpp"
#include <vector>
#include <iostream>

std::allocator<int> alloc;

TEST(CONSTRUCTOR_TEST, default_constructor)
{
    ft::vector<int>     a;
    std::vector<int>    b;

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(a.begin().base() == nullptr) << "begin is not nullptr";
    EXPECT_TRUE(a.end().base() == nullptr) << "end is not nullptr";
}

TEST(CONSTRUCTOR_TEST, default_constructor_with_explicity_alloc)
{
    ft::vector<int>     a(alloc);
    std::vector<int>    b(alloc);

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(a.begin().base() == nullptr) << "begin is not nullptr";
    EXPECT_TRUE(a.end().base() == nullptr) << "end is not nullptr";
}

TEST(CONSTRUCTOR_TEST, constructor_with_size1)
{
    ft::vector<int>     a(3);
    std::vector<int>    b(3);

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not default";
}

TEST(CONSTRUCTOR_TEST, constructor_with_size2)
{
    ft::vector<int>     a(3, 123);
    std::vector<int>    b(3, 123);

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not default";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(CONSTRUCTOR_TEST, constructor_with_size3)
{
    ft::vector<int>     a(3, 123, alloc);
    std::vector<int>    b(3, 123, alloc);

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not default";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(CONSTRUCTOR_TEST, constructor_with_iterators1)
{
    ft::vector<int>     a(3, 123);
    ft::vector<int>    b(a.begin(), a.end());

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(CONSTRUCTOR_TEST, constructor_with_iterators2)
{
    ft::vector<int>     a(15);
    for (int i = 0; i < 15; ++i)
        a[i] = i;
    ft::vector<int>    b(a.begin(), a.end());

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(CONSTRUCTOR_TEST, constructor_with_iterators3)
{
    ft::vector<int>     a(15);
    for (int i = 0; i < 15; ++i)
        a[i] = i;
    ft::vector<int>    b(a.data(), a.data() + a.size());

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(CONSTRUCTOR_TEST, constructor_with_iterators4)
{
    std::vector<int>     a(15);
    for (int i = 0; i < 15; ++i)
        a[i] = i;
    ft::vector<int>    b(a.begin(), a.end());

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(CONSTRUCTOR_TEST, constructor_with_iterators5)
{
    ft::vector<int>     a(15);
    for (int i = 0; i < 15; ++i)
        a[i] = i;
    ft::vector<int>    b(a.begin(), a.end(), alloc);

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(CONSTRUCTOR_TEST, constructor_copy)
{
    ft::vector<int>     a(15);
    for (int i = 0; i < 15; ++i)
        a[i] = i;
    ft::vector<int>    b(a);

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(OPERATOR_EQUAL, operator_equal)
{
    ft::vector<int>     a(15);
    for (int i = 0; i < 15; ++i)
        a[i] = i;
    ft::vector<int>    b = a;

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(ASSIGN, assign1)
{
    ft::vector<int>     a;
    std::vector<int>    b;
    a.assign(26, 42);
    b.assign(26, 42);


    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(ASSIGN, assign2)
{
    ft::vector<int>     a;
    EXPECT_ANY_THROW(a.assign(-23, 42));
}

TEST(ASSIGN, assign3)
{
    const ft::vector<int>     a(26, 42);
    ft::vector<int>    b(12, 24);
    b.assign(a.begin(), a.end());


    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i)
        EXPECT_EQ(a[i], b[i]) << "value " << i << " not equal";
}

TEST(ELEMENT_ACCESS, at1)
{
    ft::vector<int>     a(26, 42);
    a.at(12) = 45;


    EXPECT_EQ(a.size(), 26) << "size not equal";
    EXPECT_EQ(a.capacity(), 26) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), alloc) << "allocator not equal";
    EXPECT_EQ(a.empty(), false) << "empty";
    EXPECT_TRUE(*(a.begin().base()) == 42) << "begin is not equal";
    for (int i = 0; i < a.size(); ++i) {
        if (i == 12)
            EXPECT_EQ(a[i], 45) << "value " << i << " not equal";
        else
            EXPECT_EQ(a[i], 42) << "value " << i << " not equal";
    }
}

TEST(ELEMENT_ACCESS, at2)
{
    ft::vector<int>     a(26, 42);
    EXPECT_ANY_THROW(a.at(-12)) << "not throw";
    EXPECT_ANY_THROW(a.at(27)) << "not throw";
}

TEST(ELEMENT_ACCESS, front_back)
{
    ft::vector<int>     a(26);
    for (int i = 0; i < a.size(); ++i)
        a[i] = i;

    EXPECT_EQ(a.front(), 0) << "front wrong 1";
    EXPECT_EQ(a.back(), 25) << "back wrong 1";
    a.front() = 23;
    a.back() = 35;
    EXPECT_EQ(a.front(), 23) << "front wrong 2";
    EXPECT_EQ(a.back(), 35) << "back wrong 2";
}

TEST(ITERATORS, operators)
{
    ft::vector<int>     a(26);
    ft::vector<int>     b(26);
    ft::vector<int>::iterator i = a.begin();
    ft::vector<int>::iterator j = b.end();
    while (i != a.end()) {
        *i = i - a.begin();
        i++;
    }
    while (--j >= b.begin()) {
        *j = j - b.begin();
    }

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (size_t k = 0; k < a.size(); ++k)
        EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
}

TEST(REVERSE_ITERATORS, operators)
{
    ft::vector<int>     a(26);
    ft::vector<int>     b(26);
    ft::vector<int>::reverse_iterator i = a.rbegin();
    ft::vector<int>::reverse_iterator j = b.rend();
    while (i != a.rend()) {
        *i = a.rend() - 1 - i;
        i++;
    }
    while (--j <= b.rbegin()) {
        *j = b.rend() - 1 - j;
    }

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
    for (size_t k = 0; k < a.size(); ++k)
        EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
}

TEST(CAPACITY, max_size)
{
    ft::vector<int>     a(26);
    std::vector<int>    b(26);

    EXPECT_EQ(a.max_size(), b.max_size()) << "max_size not equal";
}

TEST(CAPACITY, reserve1)
{
    ft::vector<int>     a(26, 34);
    std::vector<int>    b(26, 34);

    for (int i = 0; i < 100; ++i)
    {
        a.reserve(i);
        b.reserve(i);

        EXPECT_EQ(a.size(), b.size()) << "size not equal";
        EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
        EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
        EXPECT_EQ(a.empty(), b.empty()) << "not empty";
        EXPECT_TRUE(*(a.begin().base()) == *(b.begin().base())) << "begin is not equal";
        for (size_t k = 0; k < a.size(); ++k)
            EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
    }
}

TEST(CAPACITY, reserve2)
{
    ft::vector<int>     a(26, 34);

    EXPECT_ANY_THROW(a.reserve(-5)) << "no throw";
    EXPECT_ANY_THROW(a.reserve(-1000)) << "no throw";
}

TEST(MODIFIERS, clear)
{
    for (int i = 0; i < 100; ++i)
    {
        ft::vector<int>     a(i, i);
        std::vector<int>    b(i, i);

        a.clear();
        b.clear();

        EXPECT_EQ(a.size(), b.size()) << "size not equal";
        EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
        EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
        EXPECT_EQ(a.empty(), b.empty()) << "not empty";
        for (size_t k = 0; k < a.size(); ++k)
            EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
    }
}

TEST(MODIFIERS, insert1)
{
    ft::vector<int>     a;
    std::vector<int>    b;
    for (int i = 0; i < 100; ++i)
    {

        a.insert(a.end(), i);
        b.insert(b.end(), i);

        EXPECT_EQ(a.size(), b.size()) << "size not equal";
        EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
        EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
        EXPECT_EQ(a.empty(), b.empty()) << "not empty";
        for (size_t k = 0; k < a.size(); ++k)
            EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
    }
}

TEST(MODIFIERS, insert2)
{
    ft::vector<int>     a;
    std::vector<int>    b;
    for (int i = 1; i < 100; ++i)
    {

        a.insert(a.end(), i,i);
        b.insert(b.end(), i, i);

        EXPECT_EQ(a.size(), b.size()) << "size not equal";
//        EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal " << i;
        EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
        EXPECT_EQ(a.empty(), b.empty()) << "not empty";
        for (size_t k = 0; k < a.size(); ++k)
            EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
    }
}

TEST(MODIFIERS, insert3)
{
    ft::vector<int>     a;
    ft::vector<int>    b;
    for (int i = 0; i < 100; ++i) {
        b.push_back(i);
    }
        a.insert(a.end(), b.begin(),b.end());

        EXPECT_EQ(a.size(), b.size()) << "size not equal";
        EXPECT_EQ(a.capacity(), b.size()) << "capacity not equal";
        EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
        EXPECT_EQ(a.empty(), b.empty()) << "not empty";
        for (size_t k = 0; k < a.size(); ++k)
            EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
}

TEST(MODIFIERS, erase1)
{
    ft::vector<int>     a;
    std::vector<int>    b;
    for (int i = 0; i < 100; ++i) {
        a.push_back(i);
        b.push_back(i);
    }

    while (!b.empty()) {
        a.erase(a.begin());
        b.erase(b.begin());
        EXPECT_EQ(a.size(), b.size()) << "size not equal";
        EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
        EXPECT_EQ(a.empty(), b.empty()) << "not empty";
        for (size_t k = 0; k < a.size(); ++k)
            EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
    }
}

TEST(MODIFIERS, erase2)
{
    ft::vector<int>     a;
    std::vector<int>    b;
    for (int i = 0; i < 100; ++i) {
        a.push_back(i);
        b.push_back(i);
    }

    while (!b.empty()) {
        a.erase(a.begin(), a.begin() + 2);
        b.erase(b.begin(), b.begin() + 2);
        EXPECT_EQ(a.size(), b.size()) << "size not equal";
        EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
        EXPECT_EQ(a.empty(), b.empty()) << "not empty";
        for (size_t k = 0; k < a.size(); ++k)
            EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
    }
}

TEST(MODIFIERS, pop_back)
{
    ft::vector<int>     a;
    std::vector<int>    b;
    for (int i = 0; i < 100; ++i) {
        a.push_back(i);
        b.push_back(i);
    }

    while (!b.empty()) {
        a.pop_back();
        b.pop_back();
        EXPECT_EQ(a.size(), b.size()) << "size not equal";
        EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
        EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
        EXPECT_EQ(a.empty(), b.empty()) << "not empty";
        for (size_t k = 0; k < a.size(); ++k)
            EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
    }
}

TEST(MODIFIERS, resize1)
{
    ft::vector<int>     a;
    std::vector<int>    b;

    a.resize(100);
    b.resize(100);

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    for (size_t k = 0; k < a.size(); ++k)
        EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
}

TEST(MODIFIERS, resize2)
{
    ft::vector<int>     a;
    std::vector<int>    b;

    a.resize(100, 23);
    b.resize(100, 23);

    EXPECT_EQ(a.size(), b.size()) << "size not equal";
    EXPECT_EQ(a.capacity(), b.capacity()) << "capacity not equal";
    EXPECT_EQ(a.get_allocator(), b.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a.empty(), b.empty()) << "not empty";
    for (size_t k = 0; k < a.size(); ++k)
        EXPECT_EQ(a[k], b[k]) << "value " << k << " not equal";
}

TEST(MODIFIERS, swap)
{
    ft::vector<int>     a1;
    ft::vector<int>     a2(123, 321);
    ft::vector<int>     a3(123, 321);

    a1.swap(a2);

    EXPECT_EQ(a2.size(), 0);
    EXPECT_EQ(a2.capacity(), 0);
    EXPECT_EQ(a2.empty(), true);

    EXPECT_EQ(a1.size(), a3.size()) << "size not equal";
    EXPECT_EQ(a1.capacity(), a3.capacity()) << "capacity not equal";
    EXPECT_EQ(a1.get_allocator(), a3.get_allocator()) << "allocator not equal";
    EXPECT_EQ(a1.empty(), a3.empty()) << "not empty";
    for (size_t k = 0; k < a3.size(); ++k)
        EXPECT_EQ(a1[k], a3[k]) << "value " << k << " not equal";
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}