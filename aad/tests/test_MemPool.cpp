#include <mempool.hpp>
#include <gtest/gtest.h>
#include <addutils.hpp>
//#include <Log.hpp>

TEST(MemPoolTest, TestEmplaceBackSingle)
{
    const size_t blocksize = 3;
    aad::MemPool<double, blocksize> dPool;
    
    double *x[13];
    for(int i = 0; i < 13; i++)
      {
        x[i] = dPool.emplace_back();
        *x[i] = random(-1,1);
      }
    /* also effectively tests iterators */
    int i = 0;
    for(auto v : dPool)
    {
      EXPECT_EQ(v, *x[i]);
      i++;
    }
    dPool.print_debug_info();
}

TEST(MemPoolTest, EmplaceBackMulti)
{
  /* tests emplace back multi */
  const size_t blocksize = 10;
  aad::MemPool<double, blocksize> dPool;
  double *x = dPool.emplace_back_multi(8);
  for(int i = 0; i < 8; i++)
  {
    x[i] = random(-1,1);
  }
  double *y[5];
  for(int i = 0; i < 5; i++)
  {
    y[i] = dPool.emplace_back();
    *y[i] = random(-1,1);
  }

  int k = 0;
  for(auto v : dPool)
  {
    if(k < 8)
    {
      EXPECT_EQ(v, x[k]);
    }
    else {
      EXPECT_EQ(*y[k-8], v);
    }
    k++;
  }
}

TEST(MemPoolTest, getMark)
{
  const size_t blocksize = 10;
  aad::MemPool<double, blocksize> dPool;
  double *x = dPool.emplace_back_multi(8);
  for(int i = 0; i < 8; i++)
  {
    x[i] = random(-1,1);
  }
  dPool.setMark();
  double *y[5];
  for(int i = 0; i < 5; i++)
  {
    y[i] = dPool.emplace_back();
    *y[i] = random(-1,1);
  }
  auto z = dPool.getMark();
  EXPECT_EQ(*z, *y[0]);

  dPool.rewindToMark();
  EXPECT_EQ(*dPool.end(), *z);

  dPool.memset();

  for(auto v : dPool)
  {
    EXPECT_LE( std::abs(v -  0), 1e-10 );
  }

}
