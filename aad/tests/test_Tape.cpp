#include <Tape.hpp>
#include<gtest/gtest.h>
#include<addutils.hpp>
TEST(Tape, Constructors)
{
    aad::Tape<double> tape;

    aad::Node<double>* node1 = tape.recordNode<0>();
    aad::Node<double>* node2 = tape.recordNode<1>();

    /* test node compile time construction */
    node2->derivative() = 12345.6789;
    node2->adjoint() = 123.456;

    std::cout << node2->derivative();
    std::cout << node2->adjoint();

    ASSERT_NEAR(node1->adjoint(), 0, 1e-10);
    ASSERT_NEAR(node2->derivative(),12345.6789, 1e-10);
    ASSERT_NEAR(node2->adjoint(), 123.456, 1e-10);

    /* runtime construction*/

    aad::Node<double>* node3 = tape.recordNode(1);
    aad::Node<double>* node4 = tape.recordNode(2);


    node3->derivative() = 3.1415;
    node4->adjoint() = 2.71;

    ASSERT_NEAR(node3->derivative(), 3.1415, 1e-10);
    ASSERT_NEAR(node4->adjoint(),2.71, 1e-10);

}

TEST(Tape, TapeState)
{
    /* test tape state */
    aad::Tape<double> tape;
    size_t tapesize = poolsize*10;

    for(int i = 0; i < tapesize; i++)
    {
        aad::Node<double>* node = tape.recordNode<2>();
        double r = random(-1,1);
        node->adjoint() = r;
    }

    size_t nel = 0;
    for (auto junk : tape)
    {
        nel++;
    }
    /* test tape has the expected number of elements */
    ASSERT_EQ(nel, tapesize);

    /* reset adjoints works properly */
    tape.resetAdjoints();
    int i = 0;
    for(auto junk : tape)
    {
        std::cout<< i << " " << junk.adjoint() << std::endl;
    }
    /* clear works properly */
    tape.clear();
    EXPECT_EQ(tape.begin(), tape.end());

    /* mark and rewind */
    double marked_value;
    size_t marked_index = 1025;
    for(int i = 0; i < tapesize; i++)
    {
        aad::Node<double>* node = tape.recordNode<2>();
        double r = random(-1,1);
        node->adjoint() = r;
        if(i == marked_index)
        {
            tape.mark();
            marked_value = r;
        }
    }
    auto mark = tape.getMark();
    --mark;
    tape.rewindToMark();
    EXPECT_EQ(mark->adjoint(), marked_value);
    EXPECT_EQ((--tape.end())->adjoint(), marked_value);
}
