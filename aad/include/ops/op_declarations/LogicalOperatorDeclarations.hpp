#ifndef LOGICALOPERATORDECLARATIONS_HPP
#define LOGICALOPERATORDECLARATIONS_HPP
namespace aad
{
template<typename STDSCALAR>
class Scalar;
template<typename STDSCALAR>
inline bool operator==(const Scalar<STDSCALAR>& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator==(const Scalar<STDSCALAR>& lhs, const STDSCALAR& rhs);
template<typename STDSCALAR>
inline bool operator==(const STDSCALAR& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator!=(const Scalar<STDSCALAR>& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator!=(const Scalar<STDSCALAR>& lhs, const STDSCALAR& rhs);
template<typename STDSCALAR>
inline bool operator!=(const STDSCALAR& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator<(const Scalar<STDSCALAR>& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator<(const Scalar<STDSCALAR>& lhs, const STDSCALAR& rhs);
template<typename STDSCALAR>
inline bool operator<(const STDSCALAR& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator>(const Scalar<STDSCALAR>& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator>(const Scalar<STDSCALAR>& lhs, const STDSCALAR& rhs);
template<typename STDSCALAR>
inline bool operator>(const STDSCALAR& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator<=(const Scalar<STDSCALAR>& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator<=(const Scalar<STDSCALAR>& lhs, const STDSCALAR& rhs);
template<typename STDSCALAR>
inline bool operator<=(const STDSCALAR& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator>=(const Scalar<STDSCALAR>& lhs, const Scalar<STDSCALAR>& rhs);
template<typename STDSCALAR>
inline bool operator>=(const Scalar<STDSCALAR>& lhs, const STDSCALAR& rhs);
template<typename STDSCALAR>
inline bool operator>=(const STDSCALAR& lhs, const Scalar<STDSCALAR>& rhs);
}
#endif // LOGICALOPERATORDECLARATIONS_HPP
