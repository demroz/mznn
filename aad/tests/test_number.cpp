#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../header/var.hpp"

using namespace rad;

template<typename T>
T func(T x[5] )
{
    /*
    * test expected behavior or + - * / 
    */
    T y;
    y = x[0]+x[1]*x[1];
    return y;
}

TEST_CASE("arithmetic operations","[arithmetic ops]")
{
    var<double> x[5], y;
    x[0] = 1.0;
    x[1] = 2.0;
    x[2] = 3.0;
    x[3] = 4.0;
    x[4] = 5.0;
}