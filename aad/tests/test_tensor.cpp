#include <gtest/gtest.h>

#include <autodiff.hpp>
#include <format>
#include <iostream>

TEST(DiffTensor, constructors) {
  aad::aTensor2 t1(2, 2), t2(2, 2);
  t1(0, 0) = 1.0;
  t1(1, 0) = 0.0;
  t1(0, 1) = 0.0;
  t1(1, 1) = 1.0;

  t2(0, 0) = 2.0;
  t2(1, 0) = 2.0;
  t2(0, 1) = 2.0;
  t2(1, 1) = 2.0;

  aad::ascalar* x;
  // std::cout<<t1*t2<<std::endl;
  Eigen::array<Eigen::IndexPair<int>, 1> product_dims = {
      Eigen::IndexPair<int>(1, 0)};

  aad::aTensor2 AB = t1.contract(t2, product_dims);
}
