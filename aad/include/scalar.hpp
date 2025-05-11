#ifndef SCALAR_HPP_
#define SCALAR_HPP__
#include "Tape.hpp"
#include "node.hpp"
#include "ops/op_declarations.hpp"

namespace aad {
template <typename STDSCALAR>
class Scalar {
 private:
  /*
   * @brief> autodiff scalar class
   */
  STDSCALAR _value;       /* float/double (TODO complex) */
  Node<STDSCALAR> *_node; /* parent op node */

  void createNode() { _node = tape->recordNode(); };

  template <size_t N>
  void createNode() {
    _node = tape->template recordNode<N>();
  };
  void createNode(size_t N) { _node = tape->recordNode(N); };

  Node<STDSCALAR> &node() const {
    /*
     *  HACK: Not a fan of this but its required to get Eigen::Tensor
     *  contractions to work correctly with this autodiff class;
     *
     *  Eigen::Tensor creates temporary node pointers that dont get assigned
     *  properly doing creation, so we force the creation of nodes on tape if
     *  the existing node in Scalar is a nullpointer.
     *
     *  */
    // REVIEW: if _node == nullptr
    if (!_node) {
      const_cast<Scalar<STDSCALAR> *>(this)->_node =
          const_cast<Scalar<STDSCALAR> *>(this)->tape->recordNode(1);
    }
    return const_cast<Node<STDSCALAR> &>(*_node);
  }

  /* unaries */
  STDSCALAR &derivative() { return _node->derivative(); };
  STDSCALAR *&parentAdjoint() { return _node->parentAdjoint(); };

  /* binary ops */
  STDSCALAR &lDer() { return _node->derivative(0); };
  STDSCALAR &rDer() { return _node->derivative(1); };

  STDSCALAR *&leftAdj() { return _node->parentAdjoint(0); };
  STDSCALAR *&rightAdj() { return _node->parentAdjoint(1); };

  /* generalization in case of n>=3 */
  /* currently none, but when I want to implent things like distributions
   * they may be useful */
  STDSCALAR &derivative(size_t n) { return _node->derivative(n); };
  STDSCALAR *&adjPtr(size_t n) { return _node->parentAdjoint(n); };

  Scalar(Node<STDSCALAR> &arg, const STDSCALAR val) : _value(val) {
    createNode<1>();
    _node->setUnaryParentAdjoint(&arg.adjoint());
    //_node->parentAdjoint() = arg.adjoint();
  }

  Scalar(Node<STDSCALAR> &lhs, Node<STDSCALAR> &rhs, const STDSCALAR val)
      : _value(val) {
    createNode<2>();
    _node->setLhsAdjoint(&lhs.adjoint());
    _node->setRhsAdjoint(&rhs.adjoint());
  }

 public:
  static thread_local Tape<STDSCALAR> *tape;
  Scalar() {};
  explicit Scalar(const STDSCALAR val) : _value(val) { createNode<0>(); };
  Scalar<STDSCALAR> &operator=(STDSCALAR val) {
    _value = val;
    createNode();
    return *this;
  }

  void putOnTape() { createNode(); };

  /* getters */
  STDSCALAR &item() { return _value; };
  STDSCALAR item() const { return _value; };
  STDSCALAR &adjoint() { return _node->adjoint(); };
  STDSCALAR adjoint() const { return _node->adjoint(); };

  void resetAdjoints() { tape->resetAdjoints(); };
  static void propagateAdjoints(typename Tape<STDSCALAR>::iterator from,
                                typename Tape<STDSCALAR>::iterator to) {
    auto it = from;
    while (it != to) {
      it->backward();
      --it;
    }
    it->backward();
  }

  void propagateAdjoints(typename Tape<STDSCALAR>::iterator to) {
    adjoint() = 1.0;
    auto from = tape->find(_node);
    propagateAdjoints(from, to);
  }

  void propagateToStart() { propagateAdjoints(tape->begin()); };
  void propagateMarkToStart() {
    propagateAdjoints(std::prev(tape->getMark()), tape->begin());
  }
  void propagateToMark() { propagateAdjoints(tape->getMark()); }

  /* math operations */
  /* operator overloads */
  /* in place operations */

  /* definitions are here because LSP doesn't like definining
   * them in separate file
   */
  Scalar<STDSCALAR> &operator+=(const Scalar<STDSCALAR> &arg) {
    *this = *this + arg;
    return *this;
  }
  Scalar<STDSCALAR> &operator+=(const STDSCALAR &arg) {
    *this = *this + arg;
    return *this;
  }
  Scalar<STDSCALAR> &operator-=(const Scalar<STDSCALAR> &arg) {
    *this = *this - arg;
    return *this;
  }
  Scalar<STDSCALAR> &operator-=(const STDSCALAR &arg) {
    *this = *this - arg;
    return *this;
  }
  Scalar<STDSCALAR> &operator*=(const Scalar<STDSCALAR> &arg) {
    *this = *this * arg;
    return *this;
  }
  Scalar<STDSCALAR> &operator*=(const STDSCALAR &arg) {
    *this = *this * arg;
    return *this;
  }
  Scalar<STDSCALAR> &operator/=(const Scalar<STDSCALAR> &arg) {
    *this = *this / arg;
    return *this;
  }
  Scalar<STDSCALAR> &operator/=(const STDSCALAR &arg) {
    *this = *this / arg;
    return *this;
  }

  /*
  ** +
  */
  friend Scalar<STDSCALAR> operator+
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend Scalar<STDSCALAR> operator+
      <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend Scalar<STDSCALAR> operator+
      <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);

  /*
   * -
   */
  friend Scalar<STDSCALAR> operator-
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend Scalar<STDSCALAR> operator-
      <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend Scalar<STDSCALAR> operator-
      <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);
  /*
   * *
   */
  friend Scalar<STDSCALAR> operator*
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend Scalar<STDSCALAR> operator*
      <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend Scalar<STDSCALAR> operator*
      <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);

  /*
   * /
   */
  friend Scalar<STDSCALAR> operator/
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend Scalar<STDSCALAR> operator/
      <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend Scalar<STDSCALAR> operator/
      <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);

  /* unary plus/minus */
  Scalar operator-() const;
  Scalar operator+() const;

  /* logic */
  friend bool operator==
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator== <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend bool operator== <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator!=
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator!= <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend bool operator!= <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator< <>(const Scalar<STDSCALAR> &lhs,
                           const Scalar<STDSCALAR> &rhs);
  friend bool operator< <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend bool operator< <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator>
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator><>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend bool operator><>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator<=
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator<= <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend bool operator<= <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator>=
      <>(const Scalar<STDSCALAR> &lhs, const Scalar<STDSCALAR> &rhs);
  friend bool operator>= <>(const Scalar<STDSCALAR> &lhs, const STDSCALAR &rhs);
  friend bool operator>= <>(const STDSCALAR &lhs, const Scalar<STDSCALAR> &rhs);

  /* mathematical operations */
  friend Scalar<STDSCALAR> log<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> log10<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> sqrt<>(const Scalar<STDSCALAR> &arg);

  friend Scalar<STDSCALAR> pow<>(const Scalar<STDSCALAR> &lhs,
                                 const STDSCALAR &rhs);
  friend Scalar<STDSCALAR> pow<>(const STDSCALAR &lhs,
                                 const Scalar<STDSCALAR> &rhs);
  friend Scalar<STDSCALAR> pow<>(const Scalar<STDSCALAR> &lhs,
                                 const Scalar<STDSCALAR> &rhs);

  friend Scalar<STDSCALAR> abs<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> exp<>(const Scalar<STDSCALAR> &arg);

  /*
   * trig functions
   *
   * sin cos tan
   * asin acos atan
   * sec csc cot
   * asec acsc acot
   * cosh sech tanh
   * acosh asech atanh
   *
   *
   */
  friend Scalar<STDSCALAR> sin<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> cos<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> tan<>(const Scalar<STDSCALAR> &arg);

  friend Scalar<STDSCALAR> sec<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> csc<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> cot<>(const Scalar<STDSCALAR> &arg);

  friend Scalar<STDSCALAR> asin<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> acos<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> atan<>(const Scalar<STDSCALAR> &arg);

  friend Scalar<STDSCALAR> asec<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> acsc<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> acot<>(const Scalar<STDSCALAR> &arg);

  friend Scalar<STDSCALAR> atan2<>(const Scalar<STDSCALAR> &lhs,
                                   const Scalar<STDSCALAR> &rhs);
  friend Scalar<STDSCALAR> atan2<>(const Scalar<STDSCALAR> &lhs,
                                   const STDSCALAR &rhs);
  friend Scalar<STDSCALAR> atan2<>(const STDSCALAR &lhs,
                                   const Scalar<STDSCALAR> &rhs);

  friend Scalar<STDSCALAR> sinh<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> cosh<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> tanh<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> asinh<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> acosh<>(const Scalar<STDSCALAR> &arg);
  friend Scalar<STDSCALAR> atanh<>(const Scalar<STDSCALAR> &arg);

  /* required by Eigen */
  /*
  const friend Scalar<STDSCALAR> &conj<>(const Scalar<STDSCALAR> &x);
  const friend Scalar<STDSCALAR> &real<>(const Scalar<STDSCALAR> &x);
  friend Scalar<STDSCALAR> imag<>(const Scalar<STDSCALAR> &x);
  friend Scalar<STDSCALAR> abs2<>(const Scalar<STDSCALAR> &x);
  */
  friend std::ostream &operator<<(std::ostream &os,
                                  Scalar<STDSCALAR> const &arg) {
    return os << "(" << arg.item() << "," << arg.adjoint() << ")";
  }
};

}  // namespace aad

#include "ops/op_definitions.hpp"
#endif  // SCALAR_H_
