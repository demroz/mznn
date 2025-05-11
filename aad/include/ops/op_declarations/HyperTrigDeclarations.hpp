#ifndef HYPERTRIGDECLARATIONS_HPP
#define HYPERTRIGDECLARATIONS_HPP

namespace aad {

template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline Scalar<STDSCALAR> sinh(const Scalar<STDSCALAR> &arg);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> cosh(const Scalar<STDSCALAR> &arg);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> tanh(const Scalar<STDSCALAR> &arg);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> asinh(const Scalar<STDSCALAR> &arg);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> acosh(const Scalar<STDSCALAR> &arg);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> atanh(const Scalar<STDSCALAR> &arg);

}  // namespace aad
#endif  // HYPERTRIGDECLARATIONS_HPP
