#ifndef COMMONMATHOPERATIONDEFINITIONS_HPP
#define COMMONMATHOPERATIONDEFINITIONS_HPP
#include <cmath>
namespace aad {
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline Scalar<STDSCALAR> log(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::log(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = 1.0 / arg.item();
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> log10(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::log10(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = 1.0 / (arg.item() * std::log(10));
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> sqrt(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::sqrt(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = 1.0 / (2 * std::sqrt(arg.item()));
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> pow(const Scalar<STDSCALAR> &lhs,
                             const STDSCALAR &rhs) {
  const STDSCALAR e = std::pow(lhs.item(), rhs);
  aad::Scalar<STDSCALAR> result(lhs.node(), e);
  result.derivative() = rhs * std::pow(lhs.item(), rhs - 1);
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> pow(const STDSCALAR &lhs,
                             const Scalar<STDSCALAR> &rhs) {
  const STDSCALAR e = std::pow(lhs, rhs.item());
  Scalar<STDSCALAR> result(rhs.node(), e);
  result.derivative() = std::pow(lhs, rhs.item()) * std::log(lhs);
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> pow(const Scalar<STDSCALAR> &lhs,
                             const Scalar<STDSCALAR> &rhs) {
  const STDSCALAR e = std::pow(lhs.item(), rhs.item());
  Scalar<STDSCALAR> result(lhs.node(), rhs.node(), e);
  result.lDer() = rhs.item() * std::pow(lhs.item(), rhs.item() - 1);
  result.rDer() = std::pow(lhs.item(), rhs.item()) * std::log(lhs.item());

  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> abs(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::abs(arg.item());
  Scalar<STDSCALAR> result(arg.node(), e);
  if (std::abs(arg.item()) < 1e-15) {
    result.derivative() = 0.0;
  } else {
    result.derivative() = arg.item() / e;
  }
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> exp(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::exp(arg.item());
  Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = e;
  return result;
}

};  // namespace aad
#endif  // COMMONMATHOPERATIONDEFINITIONS_HPP
