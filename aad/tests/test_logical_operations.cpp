#include <gtest/gtest.h>
#include <iostream>
#include <format>
#include <autodiff.hpp>

using namespace aad;

TEST(Scalar, LogicalExpressions)
{
    Scalar<double> x;
    Scalar<double> y;
    double z;

    x = 4.0;
    y = 4.0;
    z = 4.0;
    
    bool eq_n = x == y;
    bool eq_d = x == z;
    bool eq_dl = z == x;

    EXPECT_EQ(eq_n, true);
    EXPECT_EQ(eq_d, true);
    EXPECT_EQ(eq_dl, true);
    x = 4.0;
    y = 3.0;
    z = 1.0;

    bool neq_n = x!=y;
    bool neq_d = x!=z;
    bool neq_dl = z!=y;

    EXPECT_EQ(neq_n, true);
    EXPECT_EQ(neq_d, true);
    EXPECT_EQ(neq_dl, true);

    Scalar<double> one, two, three, four;
    double done, dtwo, dthree, dfour;
    one = 1.0;
    two = 2.0;
    three = 3.0;
    four = 4.0;

    done = 1.0;
    dtwo = 2.0;
    dthree = 3.0;
    dfour = 4.0;

    EXPECT_EQ( one < two, true);
    EXPECT_EQ( one < dtwo, true);
    EXPECT_EQ( one > dthree, false);
    EXPECT_EQ(dthree > two, true);
    EXPECT_EQ( done >= one, true);
    EXPECT_EQ( done <= one, true); 

}
