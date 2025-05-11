#include <gtest/gtest.h>

#include <addutils.hpp>
#include <autodiff.hpp>
#include <format>
#include <iostream>

using namespace aad;
template <typename T>
T testLog(T x[5]) {
  // T y = x[0] + log(log(x[1])) * log(x[2]) / x[3] - x[4];
  T y = log(x[2]);
  return y;
}
template <typename T>
T testSqrt(T x[5]) {
  T y = sqrt(x[0] + x[1]) / sqrt(x[1] + x[2]) * sqrt(x[3] * x[4]);
  return y;
}

template <typename T>
T testPow(T x[5]) {
  T y = pow(x[0], 2.0) + pow(x[1], x[2]) + 1.0 / pow(3.1415, x[3]) -
        pow(x[4], 0.1);
  return y;
}

template <typename T>
T testAbs(T x[5]) {
  T y = abs(x[0]) + abs(x[1]) + abs(x[2]) + abs(x[3]) / abs(x[4]);
  return y;
}

template <typename T>
T testExp(T x[5]) {
  T y = exp(x[0]) / exp(1.0 + x[1]) - exp(x[2] / exp(x[3])) * exp(x[4]);
  return y;
}

template <typename T>
void derivative(T (*f)(T *x), T x[5], T *res, T H, size_t n) {
  T y;
  y = f(x);

  for (int i = 0; i < n; i++) {
    x[i] += H;
    T yh = f(x);
    x[i] -= H;

    res[i] = 1 / H * (yh - y);
  }
}
TEST(var, Log) {
  double H = 1e-10;
  aad::ascalar::tape->clear();
  aad::ascalar::tape->rewind();
  aad::ascalar x[5];
  double xx[5];

  xx[0] = 2.0;  // random(100, 1000);
  xx[1] = 3.0;  // random(100, 1000);
  xx[2] = 4.0;  // ra ndom(100, 1000);
  xx[3] = 5.0;  // random(100, 1000);
  xx[4] = 6.0;  // random(100, 1000);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::ascalar y;
  y = testLog(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testLog, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(var, Sqrt) {
  double H = 1e-10;
  aad::ascalar::tape->clear();
  aad::ascalar::tape->rewind();
  aad::ascalar x[5];
  double xx[5];

  xx[0] = random(0, 10);
  xx[1] = random(0, 10);
  xx[2] = random(0, 10);
  xx[3] = random(0, 10);
  xx[4] = random(0, 10);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::ascalar y;
  y = testSqrt(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testSqrt, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(var, Pow) {
  double H = 1e-10;
  aad::ascalar::tape->clear();
  aad::ascalar::tape->rewind();
  aad::ascalar x[5];
  double xx[5];

  xx[0] = random(0, 1);
  xx[1] = random(0, 1);
  xx[2] = random(0, 1);
  xx[3] = random(0, 1);
  xx[4] = random(0, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::ascalar y;
  y = testPow(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testPow, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(var, Abs) {
  double H = 1e-10;
  aad::ascalar::tape->clear();
  aad::ascalar::tape->rewind();
  aad::ascalar x[5];
  double xx[5];

  xx[0] = random(-1, 1);
  xx[1] = random(-1, 1);
  xx[2] = random(-1, 1);
  xx[3] = random(-1, 1);
  xx[4] = random(-1, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::ascalar y;
  y = testAbs(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testAbs, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(var, Exp) {
  double H = 1e-10;
  aad::ascalar::tape->clear();
  aad::ascalar::tape->rewind();
  aad::ascalar x[5];
  double xx[5];

  xx[0] = random(-1, 1);
  xx[1] = random(-1, 1);
  xx[2] = random(-1, 1);
  xx[3] = random(-1, 1);
  xx[4] = random(-1, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::ascalar y;
  y = testExp(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testExp, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}
