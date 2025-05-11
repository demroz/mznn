#include <gtest/gtest.h>
#include <iostream>
#include "../header/AutodiffDouble.hpp"
TEST(Eigen, MM)
{
    Eigen::Matrix<rad::ascalar, 2,2> A, B, C;
    rad::var<double> a00,a01,a10,a11;
    rad::var<double> b00,b01,b10,b11;

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

    for(int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            std::cout<<C(i,j).item()<<" ";
        }
        std::cout<<"\n";
    }
    rad::var<double> z;
    z = C(0,0)+C(1,0)+C(0,1)+C(1,1);
    z.propagateToStart();
    std::cout << std::endl;

    std::cout<<a00.adjoint()<<std::endl;
}