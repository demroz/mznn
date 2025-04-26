#ifndef __SCALAR_HPP__
#define __SCALAR_HPP__

#include "node.hpp"
#include <vector>
#include <memory>

namespace aad
{
template<typename STDSCALAR>
class Scalar
{
    private:
        STDSCALAR _value;
        Node<double> *_node;

    public:
        /* temporary tape for testing add */
        static std::vector<std::unique_ptr<Node<double>>> tape;

        Scalar() {};

        STDSCALAR &item()          { return _value; };
        STDSCALAR item() const     { return _value; };

        STDSCALAR &adjoint()       { return _node->adjoint();};
        STDSCALAR adjoint() const  { return _node->adjoint(); };

        STDSCALAR& derivative()    { return _node->derivative(0); }
        STDSCALAR& lDer()          { return _node->derivative(0); }
        STDSCALAR& rDer()          { return _node->derivative(1); }

        STDSCALAR*& adjPtr()       { return _node->parentAdjoint(0); }
        STDSCALAR*& leftAdj()      { return _node->parentAdjoint(0); }
        STDSCALAR*& rightAdj()     { return _node->parentAdjoint(1); }
};
//template<typename STDSCALAR>
template<> std::vector<std::unique_ptr<Node<double>>> Scalar<double>::tape;
};


#endif
