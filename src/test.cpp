#include <iostream>
#include "stack.h"
#include "gtest/gtest.h"


TEST(test, test1)
{
    my_stack::stack<int> a;
    a.push(125);
    EXPECT_EQ(a.top(), 125);
    a.push(15);
    EXPECT_EQ(a.top(), 15);
    a.push(181327);
    EXPECT_EQ(a.top(), 181327);
    a.pop();
    EXPECT_EQ(a.top(), 15);
    a.pop();
    EXPECT_EQ(a.top(), 125);
}

TEST(test, test2)
{
    my_stack::stack<int> a;
    my_stack::stack<float> b;
    a.push(10);
    b.push(15);
    EXPECT_EQ(a.top(), 10);
    EXPECT_EQ(b.top(), 15.0f);
}
