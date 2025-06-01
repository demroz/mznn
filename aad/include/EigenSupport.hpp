#ifndef EIGENSUPPORT_HPP
#define EIGENSUPPORT_HPP

#include <Eigen/Eigen>

#include "scalar.hpp"

namespace rad {
template <typename T>
class var;
}

namespace Eigen {
template <typename T>
struct NumTraits<aad::Scalar<T>> : NumTraits<T> {
  typedef aad::Scalar<T> Real;
  typedef aad::Scalar<T> NonInteger;
  typedef aad::Scalar<T> Nested;
  enum {
    IsComplex = 0,
    IsInteger = 0,
    IsSigned = 1,
    RequireInitialization = 1,
    ReadCost = 1,
    AddCost = 3,
    MulCost = 3
  };
};
template<typename T, typename BinaryOp>
struct ScalarBinaryOpTraits<aad::Scalar<T>,T,BinaryOp> { typedef aad::Scalar<T> ReturnType;  };

template<typename T, typename BinaryOp>
struct ScalarBinaryOpTraits<T, aad::Scalar<T>,BinaryOp> { typedef aad::Scalar<T> ReturnType;  };

};  // namespace Eigen
#endif  // EIGENSUPPORT_HPP
