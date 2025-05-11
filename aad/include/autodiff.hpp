#ifndef AUTODIFF_HPP__
#define AUTODIFF_HPP__

#include <unsupported/Eigen/CXX11/Tensor>

#include "EigenSupport.hpp"
#include "Tape.hpp"
#include "node.hpp"
#include "scalar.hpp"
namespace aad {
using ascalar = Scalar<double>;
/* convenient scalar conversion */
using zeroTensor = Eigen::Tensor<ascalar, 0>;

/* arbitrary rank tensor */
template <size_t N>
using aTensor = Eigen::Tensor<ascalar, N>;
using aTensor1 = Eigen::Tensor<ascalar, 1>;
using aTensor2 = Eigen::Tensor<ascalar, 2>;
using aTensor3 = Eigen::Tensor<ascalar, 3>;
using aTensor4 = Eigen::Tensor<ascalar, 4>;

/* arbitrary size matrix */
using aMatrix = Eigen::MatrixX<ascalar>;
/* specifically sized matrix */
using aMatrix2 = Eigen::MatrixX2<ascalar>;
using aMatrix3 = Eigen::MatrixX3<ascalar>;
using aMatrix4 = Eigen::MatrixX4<ascalar>;

template <size_t rows, size_t cols>
using aMatrix_c = Eigen::Matrix<ascalar, rows, cols>;

/* vectors */
using aVector = Eigen::VectorX<ascalar>;
using aVector2 = Eigen::Vector2<ascalar>;
using aVector3 = Eigen::Vector3<ascalar>;
using aVector4 = Eigen::Vector4<ascalar>;
}  // namespace aad

#endif
