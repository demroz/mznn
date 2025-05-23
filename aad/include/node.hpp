#ifndef NODE_HPP__
#define NODE_HPP__

#include <iostream>
#include <stdexcept>

#include "globals.hpp"
namespace aad {
template <typename STDSCALAR>
class Node {
 public:
  /* different number of parents that generate the node
   * 0 : leaf
   * 1 : unary op ( exp, sin, cos ... )
   * 2 : binary op ( +, -, /, * )
   */
  size_t _n;
  STDSCALAR _adjointValue;
  STDSCALAR *_ptrDerivatives;
  STDSCALAR **_ptrParentAdjoints;

 public:
  Node(const size_t N = 0) : _n(N), _adjointValue(0) {};
  STDSCALAR &adjoint() { return _adjointValue; };
  STDSCALAR &derivative() {
    if (_n == 0) {
      throw std::runtime_error(
          "attempted to call derivative() on node "
          "allocated with N = 0 ( leaf node )");
    }

    return _ptrDerivatives[0];
  };
  STDSCALAR &derivative(size_t n) {
    if (!_n) {
      throw std::runtime_error(
          "attempted to call derivative() on node "
          "allocated with N = 0 ( leaf node )");
    }
    return _ptrDerivatives[n];
  };
  /* adjoint access */
  STDSCALAR &parentAdjoint() { return _ptrParentAdjoints; };

  void setUnaryParentAdjoint(STDSCALAR *adj) { _ptrParentAdjoints[0] = adj; }
  void setLhsAdjoint(STDSCALAR *adj) { _ptrParentAdjoints[0] = adj; }
  void setRhsAdjoint(STDSCALAR *adj) { _ptrParentAdjoints[1] = adj; }
  void setAdjointAtIndex(size_t ind, STDSCALAR *adj) {
    _ptrParentAdjoints[ind] = adj;
  }

  void backward() {
    if (!_n || (std::abs(_adjointValue) < TOL)) {
      return;
    }
    for (size_t i = 0; i < _n; ++i) {
      *(_ptrParentAdjoints[i]) += _ptrDerivatives[i] * _adjointValue;
    }
  }
};
}  // namespace aad
#endif
