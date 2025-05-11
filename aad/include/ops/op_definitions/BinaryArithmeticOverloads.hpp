#ifndef BINARYARITHMETICOVERLOADS_HPP__
#define BINARYARITHMETICOVERLOADS_HPP__

/*
 * @brief> implementation file for autodiff
 * +, -, *, / operations
 */

namespace aad {
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator+(const Scalar<STDSCALAR> &lhs,
                                   const Scalar<STDSCALAR> &rhs) {
  const STDSCALAR e = lhs.item() + rhs.item();

  Scalar<STDSCALAR> result(lhs.node(), rhs.node(), e);
  result.lDer() = 1.0;
  result.rDer() = 1.0;
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator+(const Scalar<STDSCALAR> &lhs,
                                   const STDSCALAR &rhs) {
  const STDSCALAR e = lhs.item() + rhs;
  Scalar<STDSCALAR> result(lhs.node(), e);
  result.derivative() = 1.0;
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator+(const STDSCALAR &lhs,
                                   const Scalar<STDSCALAR> &rhs) {
  return rhs + lhs;
}
/* OPERATOR * MULTIPLY */
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator*(const Scalar<STDSCALAR> &lhs,
                                   const Scalar<STDSCALAR> &rhs) {
  const STDSCALAR e = lhs.item() * rhs.item();
  Scalar<STDSCALAR> result(lhs.node(), rhs.node(), e);
  result.lDer() = rhs.item();
  result.rDer() = lhs.item();

  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator*(const Scalar<STDSCALAR> &lhs,
                                   const STDSCALAR &rhs) {
  const STDSCALAR e = lhs.item() * rhs;
  Scalar<STDSCALAR> result(lhs.node(), e);
  result.derivative() = rhs;

  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator*(const STDSCALAR &lhs,
                                   const Scalar<STDSCALAR> &rhs) {
  return rhs * lhs;
}
/* - */
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator-(const Scalar<STDSCALAR> &lhs,
                                   const Scalar<STDSCALAR> &rhs) {
  const STDSCALAR e = lhs.item() - rhs.item();
  Scalar result(lhs.node(), rhs.node(), e);
  result.lDer() = 1.0;
  result.rDer() = -1.0;
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator-(const Scalar<STDSCALAR> &lhs,
                                   const STDSCALAR &rhs) {
  const STDSCALAR e = lhs.item() - rhs;
  Scalar result(lhs.node(), e);
  result.derivative() = 1.0;
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator-(const STDSCALAR &lhs,
                                   const Scalar<STDSCALAR> &rhs) {
  const STDSCALAR e = lhs - rhs.item();
  Scalar result(rhs.node(), e);
  result.derivative() = -1.0;
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator/(const Scalar<STDSCALAR> &lhs,
                                   const Scalar<STDSCALAR> &rhs) {
  const STDSCALAR e = lhs.item() / rhs.item();
  Scalar<STDSCALAR> result(lhs.node(), rhs.node(), e);
  const STDSCALAR invRhs = 1.0 / rhs.item();
  result.lDer() = invRhs;
  result.rDer() = -lhs.item() * invRhs * invRhs;
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator/(const Scalar<STDSCALAR> &lhs,
                                   const STDSCALAR &rhs) {
  const STDSCALAR e = lhs.item() / rhs;
  Scalar<STDSCALAR> result(lhs.node(), e);
  result.derivative() = 1.0 / rhs;
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> operator/(const STDSCALAR &lhs,
                                   const Scalar<STDSCALAR> &rhs) {
  const STDSCALAR e = lhs / rhs.item();
  Scalar<STDSCALAR> result(rhs.node(), e);
  result.derivative() = -lhs / rhs.item() / rhs.item();
  return result;
}

}  // namespace aad
#endif  // BINARYARITHMETICOVERLOADS_HPP
