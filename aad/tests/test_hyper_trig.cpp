#include <gtest/gtest.h>
#include <iostream>
#include <format>
#include <cmath>
#include <autodiff.hpp>
#include <addutils.hpp>
using namespace aad;

template<typename T>
T testsinh(T x[5])
{
  T y = sinh(x[0])*sinh(x[1])+sinh(x[2])/sinh(x[3])-sinh(x[4]);
  return y;
}

template<typename T>
T testcosh(T x[5])
{
  T y = cosh(x[0])*cosh(x[1])+cosh(x[2])/cosh(x[3])-cosh(x[4]);
  return y;
}
template<typename T>
T testtanh(T x[5])
{
  T y = tanh(x[0])*tanh(x[1])+tanh(x[2])/tanh(x[3])-tanh(x[4]);
  return y;
}
template<typename T>
T testasinh(T x[5])
{
  T y = asinh(x[0])*asinh(x[1]);//+asinh(x[2])/asinh(x[3])-asinh(x[4]);
  return y;
}
template<typename T>
T testacosh(T x[5])
{
  T y = acosh(x[0])*acosh(x[1])+acosh(x[2])/acosh(x[3])-acosh(x[4]);
  return y;
}
template<typename T>
T testatanh(T x[5])
{
  T y = atanh(x[0])*atanh(x[1]); //*atanh(x[1])+atanh(x[2])/atanh(x[3])-atanh(x[4]);
  return y;
}
template<typename T>
T testatanhd(T x[5])
{
  T y = std::atanh(x[0])*std::atanh(x[1]); //*std::atanh(x[1])+std::atanh(x[2])/std::atanh(x[3])-std::atanh(x[4]);
  return y;
}
template<typename T>
void derivative(T (*f)(T *x), T x[5], T *res, T H, size_t n)
{
    T y;
    y = f(x);

    for(int i = 0; i < n; i++)
    {
        x[i] += H;
        T yh = f(x);
        x[i] -= H;

        res[i] = 1/H * (yh - y);
    }
}

TEST(var, sinh)
{
    double H = 1e-10;
    aad::ascalar::tape->clear();
    aad::ascalar::tape->rewind();
    aad::ascalar x[5];
    double xx[5];

    xx[0] = random(0,10);
    xx[1] = random(0,10);
    xx[2] = random(0,10);
    xx[3] = random(0,10);
    xx[4] = random(0,10);

    for(int i = 0; i < 5; i++)
    {
        x[i] = xx[i];
    }
    aad::ascalar y;
    y = testsinh(x);
    y.propagateToStart();

    double dydx[5];
    derivative(&testsinh, xx, dydx, H, 5);

    for(int i = 0; i < 5; i++)
    {
        ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
    }

}

TEST(var, cosh)
{
    double H = 1e-10;
    aad::ascalar::tape->clear();
    aad::ascalar::tape->rewind();
    aad::ascalar x[5];
    double xx[5];

    xx[0] = random(0,10);
    xx[1] = random(0,10);
    xx[2] = random(0,10);
    xx[3] = random(0,10);
    xx[4] = random(0,10);

    for(int i = 0; i < 5; i++)
    {
        x[i] = xx[i];
    }
    aad::ascalar y;
    y = testcosh(x);
    y.propagateToStart();

    double dydx[5];
    derivative(&testcosh, xx, dydx, H, 5);

    for(int i = 0; i < 5; i++)
    {
        ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
    }

}

TEST(var, tanh)
{
    double H = 1e-10;
    aad::ascalar::tape->clear();
    aad::ascalar::tape->rewind();
    aad::ascalar x[5];
    double xx[5];

    xx[0] = 1.0; //random(1,2);
    xx[1] = 2.0; //random(1,2);
    xx[2] = 3.0; //random(1,2);
    xx[3] = 4.0; //random(1,2);
    xx[4] = 5.0; //random(1,2);

    for(int i = 0; i < 5; i++)
    {
        x[i] = xx[i];
    }
    aad::ascalar y;
    y = testtanh(x);
    y.propagateToStart();

    double dydx[5];
    derivative(&testtanh, xx, dydx, H, 5);

    for(int i = 0; i < 5; i++)
    {
      //std::cout<< xx[i] << " " <<dydx[i]<< " " << x[i].adjoint() <<std::endl;
      ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
    }

}

TEST(var, asinh)
{
    double H = 1e-10;
    aad::ascalar::tape->clear();
    aad::ascalar::tape->rewind();
    aad::ascalar x[5];
    double xx[5];

    xx[0] = 1.0; //random(0,10);
    xx[1] = 2.0; //random(0,10);
    xx[2] = 3.0; //random(0,10);
    xx[3] = 4.0; //random(0,10);
    xx[4] = 5.0; //random(0,10);

    for(int i = 0; i < 5; i++)
    {
        x[i] = xx[i];
    }
    aad::ascalar y;
    y = testasinh(x);
    y.propagateToStart();

    double dydx[5];
    derivative(&testasinh, xx, dydx, H, 5);

    for(int i = 0; i < 5; i++)
    {
       ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
    }

}

TEST(var, acosh)
{
    double H = 1e-10;
    aad::ascalar::tape->clear();
    aad::ascalar::tape->rewind();
    aad::ascalar x[5];
    double xx[5];

    xx[0] = random(1,10);
    xx[1] = random(1,10);
    xx[2] = random(1,10);
    xx[3] = random(1,10);
    xx[4] = random(1,10);

    for(int i = 0; i < 5; i++)
    {
        x[i] = xx[i];
    }
    aad::ascalar y;
    y = testacosh(x);
    y.propagateToStart();

    double dydx[5];
    derivative(&testacosh, xx, dydx, H, 5);

    for(int i = 0; i < 5; i++)
    {
      //std::cout<< xx[i] << " " <<dydx[i]<< " " << x[i].adjoint() <<std::endl;
      ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
    }

}

TEST(var, atanh)
{
    double H = 1e-8;
    aad::ascalar::tape->clear();
    aad::ascalar::tape->rewind();
    aad::ascalar x[5];
    double xx[5];

    xx[0] = random(-1,1);
    xx[1] = random(-1,1);
    xx[2] = random(-1,1);
    xx[3] = random(-1,1);
    xx[4] = random(-1,1);

    for(int i = 0; i < 5; i++)
    {
        x[i] = xx[i];
    }
    aad::ascalar y;
    y = testatanh(x);
    y.propagateToStart();

    double dydx[5];
    derivative(&testatanhd, xx, dydx, H, 5);

    for(int i = 0; i < 5; i++)
    {
      //std::cout<< xx[i] << " nd " <<dydx[i]<< " ad res " << x[i].adjoint() <<std::endl;
      ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);ASSERT_NEAR(dydx[i], x[i].adjoint(), 1e-2);
    }

}
