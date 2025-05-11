#include <gtest/gtest.h>
#include "../header/node.hpp"


TEST(Node, NodeConstructors)
{
    rad::Node<double> node0;
    rad::Node<double> node1(0);
    rad::Node<double> node2(2);
    rad::Node<double> node10(10);

    EXPECT_EQ(node2.n, 2) 
        << " node with two children should have two chidlren";
    EXPECT_EQ(node10.n, 10)
        << " node with 10 children should have 10 chidlren";
    double &adj = node1.adjoint();
    adj = 1.2345;

    EXPECT_EQ(node1.adjoint(), adj)
        << "expected getter to work with adjoint";
    
    rad::set_number_of_adjoints<double>(3);
    EXPECT_EQ(node1.numAdj, 3)
        << "updated number of expected adjoints";
}