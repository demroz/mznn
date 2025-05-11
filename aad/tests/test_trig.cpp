#include <gtest/gtest.h>

#include <addutils.hpp>
#include <autodiff.hpp>
#include <format>
#include <iostream>

using namespace aad;
template <typename T>
T testsin(T x[5]) {
  T y = sin(x[0]) * sin(x[1]) + sin(x[2]) / sin(x[3]) - sin(x[4]);
  return y;
}
template <typename T>
T testcos(T x[5]) {
  T y = cos(x[0]) * cos(x[1]) + cos(x[2]) / cos(x[3]) - cos(x[4]);
  return y;
}
template <typename T>
T testtan(T x[5]) {
  T y = tan(x[0]) * tan(x[1]) + tan(x[2]) / tan(x[3]) - tan(x[4]);
  return y;
}
template <typename T>
T testasin(T x[5]) {
  T y = asin(x[0]) * asin(x[1]) + asin(x[2]) / asin(x[3]) - asin(x[4]);
  return y;
}
template <typename T>
T testacos(T x[5]) {
  T y = acos(x[0]) * acos(x[1]) + acos(x[2]) / acos(x[3]) - acos(x[4]);
  return y;
}
template <typename T>
T testatan(T x[5]) {
  T y = atan(x[0]) * atan(x[1]) + atan(x[2]) / atan(x[3]) - atan(x[4]);
  return y;
}

template <typename T>
T testatan2(T x[5]) {
  T y = atan2(x[0], x[1]) + atan2(x[2], 1.0) * atan2(2.0, x[3]) +
        atan2(x[0], x[4]);
  return y;
}

template <typename T>
T testsec(T x[5]) {
  T y = sec(x[0]) * sec(x[1]) + sec(x[2]) / sec(x[3]) - sec(x[4]);
  return y;
}
template <typename T>
T testsecd(T x[5]) {
  T y = util::sec(x[0]) * util::sec(x[1]) + util::sec(x[2]) / util::sec(x[3]) -
        util::sec(x[4]);
  return y;
}

template <typename T>
T testcsc(T x[5]) {
  T y = csc(x[0]) * csc(x[1]) + csc(x[2]) / csc(x[3]) - csc(x[4]);
  return y;
}
template <typename T>
T testcscd(T x[5]) {
  T y = util::csc(x[0]) * util::csc(x[1]) + util::csc(x[2]) / util::csc(x[3]) -
        util::csc(x[4]);
  return y;
}

template <typename T>
T testcot(T x[5]) {
  T y = cot(x[0]) * cot(x[1]) + cot(x[2]) / cot(x[3]) - cot(x[4]);
  return y;
}
template <typename T>
T testcotd(T x[5]) {
  T y = util::cot(x[0]) * util::cot(x[1]) + util::cot(x[2]) / util::cot(x[3]) -
        util::cot(x[4]);
  return y;
}

template <typename T>
T testasec(T x[5]) {
  T y = asec(x[0]) * asec(x[1]) + asec(x[2]) / asec(x[3]) - asec(x[4]);
  return y;
}

template <typename T>
T testasecd(T x[5]) {
  T y = util::asec(x[0]) * util::asec(x[1]) +
        util::asec(x[2]) / util::asec(x[3]) - util::asec(x[4]);
  return y;
}

template <typename T>
T testacsc(T x[5]) {
  T y = acsc(x[0]) * acsc(x[1]) + acsc(x[2]) / acsc(x[3]) - acsc(x[4]);
  return y;
}
template <typename T>
T testacscd(T x[5]) {
  T y = util::acsc(x[0]) * util::acsc(x[1]) +
        util::acsc(x[2]) / util::acsc(x[3]) - util::acsc(x[4]);
  return y;
}

template <typename T>
T testacot(T x[5]) {
  T y = acot(x[0]) * acot(x[1]) + acot(x[2]) / acot(x[3]) - acot(x[4]);
  return y;
}
template <typename T>
T testacotd(T x[5]) {
  T y = util::acot(x[0]) * util::acot(x[1]) +
        util::acot(x[2]) / util::acot(x[3]) - util::acot(x[4]);
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

TEST(Scalar, Sin) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 10);
  xx[1] = random(0, 10);
  xx[2] = random(0, 10);
  xx[3] = random(0, 10);
  xx[4] = random(0, 10);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testsin(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testsin, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Cos) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 10);
  xx[1] = random(0, 10);
  xx[2] = random(0, 10);
  xx[3] = random(0, 10);
  xx[4] = random(0, 10);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testcos(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testcos, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Tan) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 10);
  xx[1] = random(0, 10);
  xx[2] = random(0, 10);
  xx[3] = random(0, 10);
  xx[4] = random(0, 10);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testtan(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testtan, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Asin) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 1);
  xx[1] = random(0, 1);
  xx[2] = random(0, 1);
  xx[3] = random(0, 1);
  xx[4] = random(0, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testasin(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testasin, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Acos) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 1);
  xx[1] = random(0, 1);
  xx[2] = random(0, 1);
  xx[3] = random(0, 1);
  xx[4] = random(0, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testacos(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testacos, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, ATan) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 10);
  xx[1] = random(0, 10);
  xx[2] = random(0, 10);
  xx[3] = random(0, 10);
  xx[4] = random(0, 10);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testatan(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testatan, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, ATan2) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 1);
  xx[1] = random(0, 1);
  xx[2] = random(0, 1);
  xx[3] = random(0, 1);
  xx[4] = random(0, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testatan2(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testatan2, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}
TEST(Scalar, Sec) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 1);
  xx[1] = random(0, 1);
  xx[2] = random(0, 1);
  xx[3] = random(0, 1);
  xx[4] = random(0, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testsec(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testsecd, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Csc) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 1);
  xx[1] = random(0, 1);
  xx[2] = random(0, 1);
  xx[3] = random(0, 1);
  xx[4] = random(0, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testcsc(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testcscd, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Cot) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(0, 1);
  xx[1] = random(0, 1);
  xx[2] = random(0, 1);
  xx[3] = random(0, 1);
  xx[4] = random(0, 1);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testcot(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testcotd, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Asec) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(1, 2);
  xx[1] = random(1, 2);
  xx[2] = random(1, 2);
  xx[3] = random(1, 2);
  xx[4] = random(1, 2);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testasec(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testasecd, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Acsc) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(1, 2);
  xx[1] = random(1, 2);
  xx[2] = random(1, 2);
  xx[3] = random(1, 2);
  xx[4] = random(1, 2);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testacsc(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testacscd, xx, dydx, H, 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}

TEST(Scalar, Acot) {
  double H = 1e-10;
  aad::Scalar<double>::tape->clear();
  aad::Scalar<double>::tape->rewind();
  aad::Scalar<double> x[5];
  double xx[5];

  xx[0] = random(1, 2);
  xx[1] = random(1, 2);
  xx[2] = random(1, 2);
  xx[3] = random(1, 2);
  xx[4] = random(1, 2);

  for (int i = 0; i < 5; i++) {
    x[i] = xx[i];
  }
  aad::Scalar<double> y;
  y = testacot(x);
  y.propagateToStart();

  double dydx[5];
  derivative(&testacotd, xx, dydx, H, 5);
  for (int i = 0; i < 5; i++) {
    ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
  }
}
