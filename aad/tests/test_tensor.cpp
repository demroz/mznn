#include <gtest/gtest.h>
#include <iostream>
#include <format>
#include "../header/AutodiffUtillities.hpp"
#include "../header/AutodiffDouble.hpp"

TEST(DiffTensor, constructors)
{
    /*
    rad::aTensor<1> x(3),y(3);
    x.setValues({1., 2.,3.});
    y.setValues({4,5,6});
    std::cout<<x+y<<std::endl;

    rad::aMatrix A(3,3);
    rad::aMatrix_c<3,3> B;
    A << 1.,1.,1.,
        2.,2.,2.,
        3.,4.,5.;
    B << 1.,0.0,0.0,
        0.,1.0,0.,
        0,0.,1.;
    rad::aMatrix C(3,3);
    C = A*B;
    std::cout<<C<<std::endl;
    */
    rad::aTensor2 t1(2,2), t2(2,2);
    t1(0,0) = 1.0;
    t1(1,0) = 0.0;
    t1(0,1) = 0.0;
    t1(1,1) = 1.0;

    t2(0,0) = 2.0;
    t2(1,0) = 2.0;
    t2(0,1) = 2.0;
    t2(1,1) = 2.0;

    rad::ascalar* x;
    //std::cout<<t1*t2<<std::endl;
    Eigen::array<Eigen::IndexPair<int>, 1> product_dims = { Eigen::IndexPair<int>(1, 0) };


    rad::aTensor2 AB = t1.contract(t2, product_dims);
}