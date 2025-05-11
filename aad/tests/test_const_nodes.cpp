#include <gtest/gtest.h>

#include <addutils.hpp>
#include <autodiff.hpp>

template <typename T>
T dummy_test(T x[5], T y[5]) {
  T y1 = x[0] + y[0];
  T y2 = x[1] * y[1];
  T y3 = log(x[2]) * sinh(y[2]) - cos(x[3] / y[3]);
  T y4 = y3 * y[4] - x[4];
  T z = y1 + y2 + y3 + y4;

  return z;
}
template <typename T>
void derivative(T (*f)(T *x, T *y), T x[5], T z[5], T *dydx, T *dydz, T H,
                size_t n) {
  T y;
  y = f(x, z);

  for (int i = 0; i < n; i++) {
    x[i] += H;
    T yh = f(x, z);
    x[i] -= H;

    dydx[i] = 1 / H * (yh - y);
  }
  for (int i = 0; i < n; i++) {
    z[i] += H;
    T yh = f(x, z);
    z[i] -= H;

    dydz[i] = 1 / H * (yh - y);
  }
}
TEST(var, doesnt_requires_gaad) {
  aad::ascalar::tape->rewind();
  aad::ascalar x[5];
  aad::ascalar y[5];
  double xx[5], yy[5];

  for (int i = 0; i < 5; i++) {
    xx[i] = random(-1, 1);
    yy[i] = random(-1, 1);
    x[i] = xx[i];
    y[i] = yy[i];
  }

  aad::ascalar z = dummy_test(x, y);

  z.propagateToStart();

  double H = 1e-6;
  double dfdx[5], dfdy[5];
  derivative(&dummy_test, xx, yy, dfdx, dfdy, H, 5);

  for (int i = 0; i < 5; i++) {
    std::cout << "dz/dx= " << x[i].adjoint() << " dz/dy= " << y[i].adjoint()
              << " n dfdx= " << dfdx[i] << " n dfdy= " << dfdy[i] << std::endl;
  }
}
