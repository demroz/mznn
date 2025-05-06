#ifndef __SCALAR_HPP__
#define __SCALAR_HPP__
#include "Tape.hpp"
#include "node.hpp"
namespace aad {
template <typename STDSCALAR> class Scalar {
  public:
    static thread_local Tape<double> *tape;

  private:
  /*
   * @brief> autodiff scalar class
   */
    STDSCALAR _value;      /* float/double (TODO complex) */
    Node<STDSCALAR> *_node; /* parent op node */

    void createNode() {
      tape->iexist();
      _node = tape->recordNode();
    };

    template <size_t N> void createNode() {
      tape->iexist();
      std::cout<< "i am here" <<std::endl;
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
      _node->parentAdjoint() = arg.adjoint();
    }

    Scalar(Node<STDSCALAR> &lhs, Node<STDSCALAR> &rhs, const STDSCALAR val)
      : _value(val) {
      createNode<2>();
      _node->parentAdjoint(0) = &lhs.adjoint();
      _node->parentAdjoint(1) = &rhs.adjoint();
    }


  public:
    Scalar(){};
    explicit Scalar( const STDSCALAR val ) : _value(val) { createNode();};
    Scalar<STDSCALAR> &operator=(STDSCALAR val)
    {
      _value = val;
      createNode();
      return *this;
    }

    void putOnTape() { createNode(); };

    STDSCALAR &item() {return _value; };
    STDSCALAR item() const { return _value; };
    STDSCALAR &adjoint() { return _node->adjoint(); };
    STDSCALAR adjoint() const { return _node->adjoint(); };
    STDSCALAR &adjoint(const size_t n ) { return _node->adjoint(n); };
    STDSCALAR adjoint (const size_t n ) const { return _node->adjoint(n); };

    void resetAdjoints() { tape->resetAdjoints(); };
    static void propagateAdjoints(typename Tape<STDSCALAR>::iterator from,
                                  typename Tape<STDSCALAR>::iterator to)
    {
      auto it  = from;
      while(it != to)
      {
        it->backward();
        --it;
      }
      it->backward();
    }
    /*
    void propagateAdjoints(typename Tape<STDSCALAR>::iterator to)
    {
      adjoint() = 1.0;
      auto from = tape->find(_node);
      propagateAdjoints(from, to);
    }

    void propagateToStart() {propagateAdjoints(tape->begin());};
    void propagateMarkToStart() {propagateAdjoints(std::prev(tape->getMark()), tape->begin());}
    void propagateToMark() { propagateAdjoints(tape->getMark()) ;}
   */
    /* math operations */
    /* operator overloads */
    /*
    ** +
     */

};

} // namespace aad
#endif // SCALAR_H_
