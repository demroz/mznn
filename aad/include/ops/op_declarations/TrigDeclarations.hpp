#ifndef TRIGDECLARATIONS_HPP
#define TRIGDECLARATIONS_HPP
/* trig ops */

namespace aad
{
template<typename STDSCALAR>
class Scalar;

template<typename STDSCALAR>
inline Scalar<STDSCALAR> sin(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> cos(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> tan(const Scalar<STDSCALAR> &arg);

template<typename STDSCALAR>
inline Scalar<STDSCALAR> sec(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> csc(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> cot(const Scalar<STDSCALAR> &arg);

template<typename STDSCALAR>
inline Scalar<STDSCALAR> asin(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> acos(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> atan(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>

inline Scalar<STDSCALAR> atan2(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> atan2(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> atan2(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);

template<typename STDSCALAR>
inline Scalar<STDSCALAR> asec(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> acsc(const Scalar<STDSCALAR> &arg);
template<typename STDSCALAR>
inline Scalar<STDSCALAR> acot(const Scalar<STDSCALAR> &arg);

}; // namespace aad
#endif // TRIGDECLARATIONS_HPP
