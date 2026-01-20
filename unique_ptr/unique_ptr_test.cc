#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include "unique_ptr.h"

struct Resource
{
    Resource() { std::cout << "res ctor\n"; }
    ~Resource() { std::cout << "res destructor\n"; }
};

TEST(MyUniquePointer, Basic)
{
    // Default ctor.
    MyUniquePointer<int> up;

    {
        MyUniquePointer<int> up(new int);
        // MyUniquePointer<int> up2(up); // copy ctor error, expected.
        MyUniquePointer<int> up2(std::move(up));
        EXPECT_EQ(up.getPtr(), nullptr);
    }
};

TEST(MyUniquePointer, Release)
{
    // Default ctor.
    MyUniquePointer<int> up(new int(5));
    auto p = up.release();
    EXPECT_EQ(*p, 5);
    EXPECT_EQ(up.getPtr(), nullptr);
};

// TODO: IntArray
// TEST(MyUniquePointer, IntArray)
// {
//     MyUniquePointer<int[]> rp(new int[5]);
//     MyUniquePointer<int[]> rp2(std::move(rp));
//     EXPECT_EQ(rp.getPtr(), nullptr);
//     std::cout << "end of scope\n";

//     std::unique_ptr<int[]> p(new int[5]);
// }

TEST(MyUniquePointer, ResourceMove)
{
    MyUniquePointer<Resource> rp(new Resource);
    MyUniquePointer<Resource> rp2(std::move(rp));
    EXPECT_EQ(rp.getPtr(), nullptr);
    std::cout << "end of scope\n";

    std::unique_ptr<int> p;
}

TEST(MyUniquePointerIntArray, Basic)
{
    MyUniquePointerIntArray rp(new int[5]);
    std::cout << "end of scope\n";
}