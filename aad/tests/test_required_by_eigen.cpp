#include <gtest/gtest.h>

#include <autodiff.hpp>
#include <format>
#include <iostream>

using namespace aad;

TEST(var, EigenReq) {
  Scalar<double> x1, x2, x3, x4;
  x1 = 1.0;
  x2 = 2.0;
  x3 = 3.0;
  x4 = 4.0;
  Scalar<double> y1, y2, y3, y4;
  y1 = conj(x1);
  y2 = real(x2);
  y3 = imag(x3);
  y4 = abs2(x4);
  EXPECT_EQ(x1, y1);
  EXPECT_EQ(x2, y2);
  EXPECT_EQ(y3, 0.0);
  EXPECT_EQ(y4, 16.0);
}
