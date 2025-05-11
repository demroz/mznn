#ifndef BINARYARITHMETICOPDECLARATIONS_HPP
#define BINARYARITHMETICOPDECLARATIONS_HPP

/*
 * @brief>
 * place where +, -, *, / are declared
 */

namespace aad {
/* forward declare */
template <typename STDSCALAR>
class Scalar;

/* inplace operators */

template <typename STDSCALAR>
Scalar<STDSCALAR> operator+(const Scalar<STDSCALAR> &lhs,
                            const Scalar<STDSCALAR> &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator+
    (const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator+
    (const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator+
    (const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);

/*
 * -
 */

template <typename STDSCALAR>
Scalar<STDSCALAR> operator-
    (const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator-
    (const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator-
    (const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);
/*
 * *
 */

template <typename STDSCALAR>
Scalar<STDSCALAR> operator*
    (const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator*
    (const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator*
    (const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);

/*
 * /
 */

template <typename STDSCALAR>
Scalar<STDSCALAR> operator/
    (const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator/
    (const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);

template <typename STDSCALAR>
Scalar<STDSCALAR> operator/
    (const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);
};  // namespace aad
#endif // BINARYARITHMETICOPDECLARATIONS_HPP
