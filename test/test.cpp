#include <iostream>
#include "stack.h"
#include "gtest/gtest.h"

TEST(initialization_and_methods, test1)
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
    EXPECT_EQ(a.pop(), 125);
    // EXPECT_DEATH(a.top(), "stack is empty");
}

TEST(initialization_and_methods, test2)
{
    my_stack::stack<int> a;
    my_stack::stack<float> b;
    a.push(10);
    b.push(15);
    EXPECT_EQ(a.top(), 10);
    EXPECT_EQ(b.top(), 15.0f);
}

TEST(constructors, copying)
{
    my_stack::stack<int> a;
    a.push(15);
    my_stack::stack<int> b(a);
    EXPECT_EQ(b.top(), 15);
    EXPECT_EQ(a.top(), 15);
}

TEST(constructors, moving)
{
    my_stack::stack<int> a;
    a.push(15);
    my_stack::stack<int> b(std::move(a));
    EXPECT_EQ(b.top(), 15);
}

TEST(constructors, assigment_copying)
{
    my_stack::stack<int> a;
    a.push(10);
    my_stack::stack<int> b;
    b.push(15);
    a = b;
    EXPECT_EQ(a.top(), 15);
}

TEST(constructors, assigment_moving)
{
    my_stack::stack<int> a;
    a.push(15);
    my_stack::stack<int> b;
    b = std::move(a);
    EXPECT_EQ(b.top(), 15);
}
