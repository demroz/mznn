#include "../include/addutils.hpp"

double random(double LO, double HI)
{
    /* silly random number generator */
    double r3 = LO + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (HI - LO)));
    return r3;
}
