#include <gtest/gtest.h>

#include <autodiff.hpp>

template <typename T>
T arithmetic_test(T x[5]) {
  T y = x[0] + x[1] * x[2] / x[3] - x[4];

  return y;
}

double random(double LO, double HI) {
  double r3 = LO + static_cast<double>(rand()) /
                       (static_cast<float>(RAND_MAX / (HI - LO)));
  return r3;
}
TEST(scalars, Constructors) {
  aad::ascalar x(1.0);
  ASSERT_NEAR(x.item(), 1.0, 1e-10);
  aad::ascalar y;
  y = 13.0;
  ASSERT_NEAR(y.item(), 13, 1e-10);
}

TEST(scalars, Arithmetic) {
  aad::ascalar::tape->rewind();
  aad::ascalar x[5];
  double xx[5];

  xx[0] = random(-10, 10);
  xx[1] = random(-10, 10);
  xx[2] = random(-10, 10);
  xx[3] = random(-10, 10);
  xx[4] = random(-10, 10);
  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }

  double yy = arithmetic_test(xx);
  double ndydx[5];
  double h = 1e-10;
  for (int i = 0; i < 5; i++) {
    double fh;
    xx[i] += h;
    fh = arithmetic_test(xx);
    xx[i] -= h;
    ndydx[i] = (fh - yy) / h;
  }

  aad::ascalar fx = arithmetic_test(x);
  fx.propagateToStart();
  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(x[i].item(), xx[i], 1e-6);
  }
  x[0] += x[1];
}
