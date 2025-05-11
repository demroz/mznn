#ifndef COMMONMATHOPERATIONS_HPP
#define COMMONMATHOPERATIONS_HPP
#include <cmath>
/* overloads common math operations
 *
 *  currently implemented
 *
 * sqrt
 * pow
 * exp
 * log
 * log10
 *
 */
namespace aad {
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline Scalar<STDSCALAR> log(const Scalar<STDSCALAR> &arg);

template <typename STDSCALAR>
inline Scalar<STDSCALAR> log10(const Scalar<STDSCALAR> &arg);

template <typename STDSCALAR>
inline Scalar<STDSCALAR> sqrt(const Scalar<STDSCALAR> &arg);

template <typename STDSCALAR>
inline Scalar<STDSCALAR> pow(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> pow(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);

template <typename STDSCALAR>
inline Scalar<STDSCALAR> pow(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);

template <typename STDSCALAR>
inline Scalar<STDSCALAR> abs(const Scalar<STDSCALAR> &arg);
template <typename STDSCALAR>
inline Scalar<STDSCALAR> exp(const Scalar<STDSCALAR> &arg);
};  // namespace rad
#endif  // COMMONMATHOPERATIONS_HPP
