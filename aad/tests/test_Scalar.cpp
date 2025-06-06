#include <gtest/gtest.h>

#include <autodiff.hpp>
TEST(BasicScalarOps, Scalars) {
  aad::ascalar x(55.0);
  aad::Scalar<double> y(3.0);
  aad::Scalar<double> z;
  z = x - y;
  LOG_INFO("z = x - y ", z.item());
  z.adjoint() = 1.0;
  z.propagateToStart();
  std::cout << x.adjoint() << " " << y.adjoint() << " " << z.adjoint()
            << std::endl;
}
