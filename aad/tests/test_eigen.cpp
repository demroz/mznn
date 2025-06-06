#include <gtest/gtest.h>
#include <iostream>
#include <autodiff.hpp>
#include <typeinfo>
TEST(Eigen, MM)
{
    Eigen::Matrix<aad::ascalar, 2,2> A, B, C;
    aad::Scalar<double> a00,a01,a10,a11;
    aad::Scalar<double> b00,b01,b10,b11;

    a00 = 1.0;
    a01 = 0.0;
    a10 = 1.0;
    a11 = 1.0;
    b00 = 2.0;
    b01 = 3.0;
    b10 = 1.0;
    b11 = std::sqrt(2);

    A(0,0) = a00;
    A(0,1) = a01;
    A(1,0) = a10;
    A(1,1) = a11;

    B(0,0) = b00;
    B(0,1) = b01;
    B(1,0) = b10;
    B(1,1) = b11;

    C = A*B;

    aad::Scalar<double> z;
    z = C(0,0)+C(1,0)+C(0,1)+C(1,1);
    z.propagateToStart();

}

TEST(Eigen, matrixmultiplydoublescalar)
{
    Eigen::Matrix<double, 2, 2> A;
    Eigen::Matrix<aad::ascalar, 2,2> B;

    A(0,0) = 1.0;
    A(0,1) = 2.0;
    A(1,0) = 2.0;
    A(1,1) = 1.0;

    B(0,0) = std::sqrt(2);
    B(1,1) = 1.0;

    auto C = A*B;
}
