#ifndef TRIGFUNCTIONOVERLOADS_HPP
#define TRIGFUNCTIONOVERLOADS_HPP
#include <cmath>
namespace util {
template <typename STDSCALAR>
inline STDSCALAR sec(const STDSCALAR &arg) {
  return 1.0 / std::cos(arg);
}
template <typename STDSCALAR>
inline STDSCALAR csc(const STDSCALAR &arg) {
  return 1.0 / std::sin(arg);
}
template <typename STDSCALAR>
inline STDSCALAR cot(const STDSCALAR &arg) {
  return 1.0 / std::tan(arg);
}
template <typename STDSCALAR>
inline STDSCALAR asec(const STDSCALAR &arg) {
  return std::acos(1.0 / arg);
}
template <typename STDSCALAR>
inline STDSCALAR acsc(const STDSCALAR &arg) {
  return std::asin(1.0 / arg);
}
template <typename STDSCALAR>
inline STDSCALAR acot(const STDSCALAR &arg) {
  return std::atan(1.0 / arg);
}
}  // namespace util
namespace aad {
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline Scalar<STDSCALAR> sin(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::sin(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = std::cos(arg.item());
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> cos(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::cos(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = -std::sin(arg.item());
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> tan(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::tan(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = std::pow(util::sec(arg.item()), 2);
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> asin(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::asin(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = 1.0 / std::sqrt(1 - arg.item() * arg.item());
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> acos(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::acos(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = -1.0 / std::sqrt(1 - arg.item() * arg.item());
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> atan(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = std::atan(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = 1.0 / (1 + arg.item() * arg.item());
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> atan2(const Scalar<STDSCALAR> &y,
                               const Scalar<STDSCALAR> &x) {
  const STDSCALAR e = std::atan2(y.item(), x.item());
  aad::Scalar<STDSCALAR> result(y.node(), x.node(), e);
  result.lDer() = x.item() / (x.item() * x.item() + y.item() * y.item());
  result.rDer() = -y.item() / (x.item() * x.item() + y.item() * y.item());
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> atan2(const Scalar<STDSCALAR> &y, const STDSCALAR &x) {
  const STDSCALAR e = std::atan2(y.item(), x);
  aad::Scalar<STDSCALAR> result(y.node(), e);
  result.derivative() = x / (x * x + y.item() * y.item());
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> atan2(const STDSCALAR &y, const Scalar<STDSCALAR> &x) {
  const STDSCALAR e = std::atan2(y, x.item());
  aad::Scalar<STDSCALAR> result(x.node(), e);
  result.derivative() = -y / (x.item() * x.item() + y * y);
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> sec(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = util::sec(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = util::sec(arg.item()) * std::tan(arg.item());
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> csc(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = util::csc(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = -util::csc(arg.item()) * util::cot(arg.item());
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> cot(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = util::cot(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = -util::csc(arg.item()) * util::csc(arg.item());
  return result;
}

template <typename STDSCALAR>
inline Scalar<STDSCALAR> asec(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = util::asec(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() =
      1.0 / (arg.item() * arg.item() *
             std::sqrt(1.0 - 1.0 / (arg.item() * arg.item())));
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> acsc(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = util::acsc(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() =
      -1.0 / (arg.item() * arg.item() *
              std::sqrt(1.0 - 1.0 / (arg.item() * arg.item())));
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> acot(const Scalar<STDSCALAR> &arg) {
  const STDSCALAR e = util::acot(arg.item());
  aad::Scalar<STDSCALAR> result(arg.node(), e);
  result.derivative() = -1.0 / (arg.item() * arg.item() + 1.0);
  return result;
}

}  // namespace aad
#endif  // TRIGFUNCTIONOVERLOADS_HPP
