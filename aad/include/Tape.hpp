#ifndef __TAPE_HPP__
#define __TAPE_HPP__
#include "globals.hpp"
#include "mempool.hpp"
#include "node.hpp"

namespace aad {

template <typename T> class Tape {
  private:
    MemPool<Node<T>, poolsize> _nodes;
    MemPool<T, poolsize> _derivatives;
    MemPool<T *, poolsize> _ptrParentAdjoints;

    template<typename U>
    friend class Scalar;
  public:
    Tape() {
        _nodes.clear();
        _derivatives.clear();
        _ptrParentAdjoints.clear();
        LOG_INFO("cleared tape");
    }
    ~Tape() = default;

    Node<T> *recordNode() {
        /* leaf node */
        Node<T> *node = _nodes.emplace_back();
        return node;
    }

    template <size_t N> constexpr Node<T> *recordNode() {
        Node<T> *node = _nodes.emplace_back(N);
        if constexpr (N > 0) {
            /* gross syntax */
            node->_ptrDerivatives =
                _derivatives.template emplace_back_multi<N>();
            node->_ptrParentAdjoints =
                _ptrParentAdjoints.template emplace_back_multi<N>();
        }
        return node;
    }

    Node<T> *recordNode(size_t N) {
        Node<T> *node = _nodes.emplace_back(N);
        if (N > 0) {
            node->_ptrDerivatives = _derivatives.emplace_back_multi(N);
            node->_ptrParentAdjoints = _ptrParentAdjoints.emplace_back_multi(N);
        }
        return node;
    }

    void resetAdjoints() {
        int i = 0;
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            it->_adjointValue = 0;
        }
    }
    void clear() {
        _nodes.clear();
        _derivatives.clear();
        _ptrParentAdjoints.clear();
    }
    void rewind() {
        _nodes.rewind();
        _derivatives.rewind();
        _ptrParentAdjoints.rewind();
    }
    void mark() {
        _nodes.setMark();
        _derivatives.setMark();
        _ptrParentAdjoints.setMark();
    }
    void rewindToMark() {
        _nodes.rewindToMark();
        _derivatives.rewindToMark();
        _ptrParentAdjoints.rewindToMark();
    }

    using iterator = typename MemPool<Node<T>, poolsize>::Iterator;
    auto begin() { return _nodes.begin(); }
    auto end() { return _nodes.end(); }
    auto getMark() { return _nodes.getMark(); }
    auto find(Node<T> *node) { return find(node); }
    void iexist()
    {
        std::cout<<"this is sum bullshit"<<std::endl;
    }

};
} // namespace aad

#endif // TAPE_H_
