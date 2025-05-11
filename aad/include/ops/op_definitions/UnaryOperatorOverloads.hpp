#ifndef UNARYOPERATOROVERLOADS_HPP
#define UNARYOPERATOROVERLOADS_HPP

namespace aad {
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline Scalar<STDSCALAR> Scalar<STDSCALAR>::operator-() const {
  return 0.0 - *this;
}

template <typename STDSCALAR>
Scalar<STDSCALAR> Scalar<STDSCALAR>::operator+() const {
  return *this;
}
}  // namespace aad
#endif  // UNARYOPERATOROVERLOADS_HPP
