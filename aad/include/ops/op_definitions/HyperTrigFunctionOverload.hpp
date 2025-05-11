#ifndef HYPERTRIGFUNCTIONOVERLOAD_HPP
#define HYPERTRIGFUNCTIONOVERLOAD_HPP
#include <cmath>

namespace aad {
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline Scalar<STDSCALAR> sinh(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::sinh(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = std::cosh(arg.item());
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> cosh(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::cosh(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = std::sinh(arg.item());
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> tanh(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::tanh(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = 1.0 / (std::pow(std::cosh(arg.item()), 2));
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> asinh(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::asinh(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = 1.0 / (std::sqrt(1.0 + std::pow(arg.item(), 2)));
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> acosh(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::acosh(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() =
      1.0 / (std::sqrt(arg.item() - 1.0) * std::sqrt(arg.item() + 1));
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> atanh(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::atanh(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = -1.0 / ((arg.item() - 1.0) * (arg.item() + 1.0));
  return result;
}

}  // namespace aad
#endif  // HYPERTRIGFUNCTIONOVERLOAD_HPP
