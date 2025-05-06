#ifndef __OP_DECLARATIONS_HPP__
#define __OP_DECLARATIONS_HPP__

/*
** file needed for declaring functions of
** templated classes
**
*/

namespace aad
{
    template<typename STDSCALAR>
    class Scalar;

    template<typename STDSCALAR>
    inline Scalar<STDSCALAR> operator+(const Scalar<STDSCALAR> &lhs,
                                    const Scalar<STDSCALAR> &rhs);
};
#endif
