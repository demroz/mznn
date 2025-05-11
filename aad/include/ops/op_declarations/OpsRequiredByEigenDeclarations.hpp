#ifndef OPSREQUIREDBYEIGENDECLARATIONS_HPP
#define OPSREQUIREDBYEIGENDECLARATIONS_HPP
namespace aad {
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline const Scalar<STDSCALAR>& conj(const Scalar<STDSCALAR>& x);
template <typename STDSCALAR>
inline const Scalar<STDSCALAR>& real(const Scalar<STDSCALAR>& x);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> imag(const Scalar<STDSCALAR>& x);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> abs2(const Scalar<STDSCALAR>& x);
}  // namespace aad
#endif  // OPSREQUIREDBYEIGENDECLARATIONS_HPP
