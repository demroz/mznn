#ifndef OPSREQUIREDBYEIGENOVERLOADS_HPP
#define OPSREQUIREDBYEIGENOVERLOADS_HPP
namespace aad {
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline const Scalar<STDSCALAR>& conj(const Scalar<STDSCALAR>& x) {
  return x;
}
template <typename STDSCALAR>
inline const Scalar<STDSCALAR>& real(const Scalar<STDSCALAR>& x) {
  return x;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> imag(const Scalar<STDSCALAR>& x) {
  const STDSCALAR e = 0.0;
  aad::Scalar<STDSCALAR> result(x.node(), e);
  result.derivative() = 0.0;
  return result;
}
template <typename STDSCALAR>
inline Scalar<STDSCALAR> abs2(const Scalar<STDSCALAR>& x) {
  return x * x;
}
}  // namespace aad
#endif  // OPSREQUIREDBYEIGENOVERLOADS_HPP
