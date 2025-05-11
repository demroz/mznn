#include <gtest/gtest.h>
#include "../header/node.hpp"
#include "../header/memory_manager.hpp"
#include <iostream>
#include <format>

TEST(MemoryPool, Constructors)
{
    /* check that things are getting allocated on tape */
    rad::MemoryPool<rad::Node<double>, 5> nodePool;
    rad::MemoryPool<double, 5> dPool;
    rad::MemoryPool<double *, 5> dpPool;

    /* test base double pool constructor */
    double *x[6];
    x[0] = dPool.emplace_back();
    x[1] = dPool.emplace_back();
    x[2] = dPool.emplace_back();
    x[3] = dPool.emplace_back();
    x[4] = dPool.emplace_back();
    x[5] = dPool.emplace_back();

    *x[0] = 1.0;
    *x[1] = 2.0;
    *x[2] = 3.0;
    *x[3] = 4.0;
    *x[4] = 5.0;
    *x[5] = 6.0;

    int k = 0;
    for(auto it = dPool.begin(); it != dPool.end(); it++)
    {
        EXPECT_EQ(*x[k],*it) 
            << "Value not properly assigned";
        k++;
    }
    EXPECT_EQ(*dPool.begin(),*x[0]);
    EXPECT_EQ(*dPool.end()--,*x[5]);

    /* test rewind */
    dPool.rewind();
    EXPECT_EQ(*dPool.begin(),*x[0]);
    int l = 0;

    /* mark test */
    for(auto it = dPool.begin(); it != dPool.end(); it++)
    {
        if(l==3)
        {
            dPool.setmark();
        }
        dPool.nextitem();
        l++;

    }
    /* TODO: fix?? */
    //EXPECT_EQ(*dPool.mark(),*x[3]);
    
    /* test clear function */
    dPool.clear();
    EXPECT_EQ(*dPool.begin(), 0.0)
        << "Memroy not creaed properly";
    EXPECT_EQ(dPool.begin(), dPool.end())
         << "Memroy not creaed properly";

    /* empalace back multi at runtime */
    double *y = dPool.emplace_back_multi(5);
    y[0] = 12.;
    y[1] = 13.;
    y[2] = 14.;
    y[3] = 15.;
    y[4] = 16.;

    EXPECT_THROW({
        try
        {
            dPool.emplace_back_multi(6);
        }
        catch( const std::out_of_range& e )
        {
            // and this tests that it has the correct message
            std::string what;
            what  = std::format("attempted to insert {} elements while block size is {}",6,5);
            
            EXPECT_EQ( what, e.what() );
            throw;
        }
    }, std::out_of_range );
    /* clear memory */
    dPool.clear();

    /* emplace_back_multi compile time */
    double *z = dPool.emplace_back_multi<5>();
    z[0] = 12.;
    z[1] = 13.;
    z[2] = 14.;
    z[3] = 15.;
    z[4] = 16.;
    
    
    EXPECT_THROW({
        try
        {
            dPool.emplace_back_multi<6>();
        }
        catch( const std::out_of_range& e )
        {
            std::string what;
            what  = std::format("attempted to insert {} elements while block size is {}",6,5);
            EXPECT_EQ( what, e.what() );
            throw;
        }
    }, std::out_of_range );
    
    dPool.memset();
    for(auto it = dPool.begin(); it != dPool.end(); it++)
    {
        ASSERT_NEAR(*it,0.0, 1e-10);
    }   
}
