#ifndef LOGICALOPERATORDEFINITIONS_HPP
#define LOGICALOPERATORDEFINITIONS_HPP
namespace aad{
template <typename STDSCALAR>
class Scalar;

template <typename STDSCALAR>
inline bool operator==(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs.item() == rhs.item();
}
template <typename STDSCALAR>
inline bool operator==(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs)
{
  return lhs.item() == rhs;
}

template <typename STDSCALAR>
inline bool operator==(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs == rhs.item();
}

template <typename STDSCALAR>
inline bool operator!=(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs.item() != rhs.item();
}

template <typename STDSCALAR>
inline bool operator!=(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs)
{
  return lhs.item() != rhs;
}

template <typename STDSCALAR>
inline bool operator!=(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs != rhs.item();
}

template <typename STDSCALAR>
inline bool operator<(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs.item() < rhs.item();
}

template <typename STDSCALAR>
inline bool operator<(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs)
{
  return lhs.item() < rhs;
}

template <typename STDSCALAR>
inline bool operator<(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs < rhs.item();
}

template <typename STDSCALAR>
inline bool operator>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs.item() > rhs.item();
}

template <typename STDSCALAR>
inline bool operator>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs)
{
  return lhs.item() > rhs;
}

template <typename STDSCALAR>
inline bool operator>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs > rhs.item();
}


template <typename STDSCALAR>
inline bool operator<=(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs.item() <= rhs.item();
}

template <typename STDSCALAR>
inline bool operator<=(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs)
{
  return lhs.item() <= rhs;
}

template <typename STDSCALAR>
inline bool operator<=(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs <= rhs.item();
}

template <typename STDSCALAR>
inline bool operator>=(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs.item() >= rhs.item();
}
template <typename STDSCALAR>
inline bool operator>=(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs)
{
  return lhs.item() >= rhs;
}
template <typename STDSCALAR>
inline bool operator>=(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs)
{
  return lhs >= rhs.item();
}
};
#endif // LOGICALOPERATORDEFINITIONS_HPP
