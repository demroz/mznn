/**
 * @author Maksym Zhelyeznyakov
 *
 * @brief Memory pool for AAD class based on small object allocation
 * optimization allocates memory for many small objects at once
 *
 */
#ifndef __MEMPOOL_HPP__
#define __MEMPOOL_HPP__

#include "LogManager.hpp"
#include <array>
#include <cstddef>
#include <cstring> // for memset
#include <iterator>
#include <list>
#include <log.hpp>
#include <stdexcept>
namespace aad {
template <typename MemPool> class PoolIterator {
    /**
     * @brief enables iterating over pool with
     * c++ iterators
     */
  public:
    /* type declarations */
    using ValueType = typename MemPool::ValueType;
    using PointerType = typename MemPool::ValueType *;
    using ReferenceType = typename MemPool::ValueType &;
    using iteratorCategory = std::bidirectional_iterator_tag;
    using difference_type = ptrdiff_t;
    using blockIterator = typename MemPool::blockIterator;
    using itemIterator = typename MemPool::itemIterator;
  private:
    /* iterators */
    blockIterator _currentBlock;
    blockIterator _firstBlock;
    blockIterator _lastBlock;

    itemIterator _currentItem;
    itemIterator _lastItemInPool;

  public:
    PoolIterator() {};
    /* constructor */
    PoolIterator(blockIterator firstBlock, blockIterator lastBlock,
                 blockIterator currentBlock, itemIterator currentItem,
                 itemIterator lastItem)
        : _firstBlock(firstBlock), _lastBlock(lastBlock),
          _currentItem(currentItem), _currentBlock(currentBlock),
          _lastItemInPool(lastItem) {};

    /* getters */
    blockIterator getCurrentBlock() { return _currentBlock; }
    blockIterator getFirstBlock() { return _firstBlock; }
    blockIterator getLastBlock() { return _lastBlock; }
    itemIterator getCurrentItem() { return _currentItem; }
    itemIterator getLastItemInPool() { return _lastItemInPool; }

    PoolIterator &operator++() {
        /**
         * @brief iterates over current item by 1 and skips to next block if
         * needed
         */

        ++_currentItem;
        if (_currentItem == _lastItemInPool) {
            return *this;
        }
        if (_currentItem == _currentBlock->end()) {
            ++_currentBlock;
            if (_currentBlock == _lastBlock) {
                throw std::out_of_range(
                    "block out of range. this will case a segfault");
            }
            _currentItem = _currentBlock->begin();
        }
        return *this;
    }
    PoolIterator &operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }
    PoolIterator &operator--() {
        if (_currentItem == _currentBlock->begin()) {
            if (_currentBlock == _firstBlock) {
                throw std::out_of_range("out of range");
            }

            --_currentBlock;
            _currentItem = _currentBlock->end();
        }
        --_currentItem;
        return *this;
    }
    PoolIterator &operator--(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }
    ReferenceType operator[](size_t ind) {
        /* this SHOULD work */
        /* TODO test it */
        return &*(_currentItem) + ind;
    }

    PointerType operator->() { return &*_currentItem; }
    const PointerType operator->() const { return &*_currentItem; }

    ReferenceType operator*() { return *_currentItem; }
    const ReferenceType operator*() const { return *_currentItem; }
    bool operator==(const PoolIterator &rhs) const {
        return ((_currentItem == rhs._currentItem) &&
                (_currentBlock == rhs._currentBlock));
    }
    bool operator!=(const PoolIterator &rhs) const {
        return ((_currentItem != rhs._currentItem) ||
                (_currentBlock != rhs._currentBlock));
    };
};
template <typename T, size_t block_size> class MemPool {
    /*
    ** Small object optimization class for AAD
    ** but useful for other things to. Vastly speeds up
    ** allocation of small objects by requesting memory
    ** in chunks
    */
  private:
    /* container */
    std::list<std::array<T, block_size>> _data;

    /* iterators */
  public:
    using blockIterator = decltype(_data.begin());
    using itemIterator = decltype(_data.begin()->begin());
    using ValueType = T;
    using Iterator = PoolIterator<MemPool<T, block_size>>;

  private:
    blockIterator _currentBlock;
    blockIterator _lastBlock;
    blockIterator _markedBlock;

    itemIterator _nextFreeSpace;
    itemIterator _markedItem;

    void _newblock() {
        /* allocates new block of memory and resets
         * iterators correctly
         * */

        _data.emplace_back();
        _currentBlock = _lastBlock = std::prev(_data.end());
        _nextFreeSpace = _currentBlock->begin();
    }

    void _nextblock() {
        /* checks if new memory needs to be allocated, if not
         * just iterates to the next block, to be used when
         * reusing already generated memory pool
         * */
        if (_currentBlock == std::prev(_data.end())) {
            LOG_DEBUG("pool full, calling _newblock()");
            _newblock();
        } else {
            LOG_DEBUG("space exists in pool, incrementing");
            ++_currentBlock;
            _nextFreeSpace = _currentBlock->begin();
        }
    }

  public:
    MemPool() {
        _newblock();
        _markedBlock = _currentBlock;
        _markedItem = _nextFreeSpace;
    };
    ~MemPool() { /* not needed, primitive containers handle destruction */ };

    void clear() {
        _data.clear();
        _newblock();
    }
    void rewind() {
        _nextFreeSpace = _data.begin().begin();
        _currentBlock = _data.begin();
    }
    void setMark() {
        _markedBlock = _currentBlock;
        _markedItem = _nextFreeSpace;
    }
    void rewindToMark() {
        _currentBlock = _markedBlock;
        _nextFreeSpace = _markedItem;
    }
    void memset(unsigned char value = 0) {
        for (auto &arr : _data) {
            std::memset(&arr[0], value, block_size * sizeof(T));
        }
    }

    T *emplace_back() {
        if (_nextFreeSpace == _currentBlock->end()) {
            _nextblock();
        }
        auto ret = _nextFreeSpace;
        ++_nextFreeSpace;
        LOG_DEBUG("called emplace back with without arguments");
        return &*ret;
    }
    /* this may cause fragmentation
     * TODO
     * fix when building Tape class
     * */
    template <size_t n> T *emplace_back_multi() {
        if (std::distance(_nextFreeSpace, _currentBlock->end()) < n) {
            LOG_INFO("distance to end < n");
            _nextblock();
        }
        auto ret = _nextFreeSpace;
        _nextFreeSpace += n;
        LOG_DEBUG("called compiled time emplace back with size_t n {}", n);
        LOG_DEBUG("return address: {} begin address: {}",
                  reinterpret_cast<std::uintptr_t>(&*ret),
                  reinterpret_cast<std::uintptr_t>(_data.begin()->begin()));
        return &*ret;
    }
    T *emplace_back_multi(size_t n) {
        LOG_INFO("calling empalce back muilti at runtime");
        if (std::distance(_nextFreeSpace, _currentBlock->end()) < n) {
            _nextblock();
        }
        auto ret = _nextFreeSpace;
        _nextFreeSpace += n;
        LOG_INFO("called run time emplace back with size_t n {}", n);
        LOG_INFO("return address: {} begin address: {} end address: {}",
                 reinterpret_cast<std::uintptr_t>(&*ret),
                 reinterpret_cast<std::uintptr_t>(_data.begin()->begin()),
                 reinterpret_cast<std::uintptr_t>(&*end()));
        return &*ret;
    }

    template <typename... Args> T *emplace_back(Args &&...args) {
        /* implements perfect forwarding
         * of constructor arguments
         * for a good explanation of this read
         * chapter 10 of
         * Savine, Antoine. Modern Computational Finance:
         * AAD and Parallel Simulations,
         * John Wiley & Sons, Inc., Hoboken, New Jersey, 2019.
         * */
        // No more space in current array
        if (_nextFreeSpace == _currentBlock->end()) {
            _nextblock();
        }
        T *emplaced = new (&*_nextFreeSpace) T(std::forward<Args>(args)...);
        ++_nextFreeSpace;
        LOG_DEBUG("called empalce back with perfect forwarding");
        return emplaced;
    }
    Iterator begin() {
        LOG_INFO("iterator begin");
        return Iterator(_data.begin(), _data.end(), _data.begin(),
                        _data.begin()->begin(), _nextFreeSpace);
    }
    Iterator end() {
        LOG_INFO("iterator end");
        return Iterator(_data.begin(), _data.end(), _currentBlock,
                        _nextFreeSpace, _nextFreeSpace);
    }

    Iterator getMark() {
        LOG_INFO("get mark");
        return Iterator(_data.begin(), _data.end(), _markedBlock, _markedItem,
                        _nextFreeSpace);
    }

    Iterator find(const T *const item) {
        Iterator start = begin();
        Iterator it = end();
        while (it != start) {
            --it;
            if (&*it == item) {
                return it;
            }
        }
        if (&*it == item) {
            return it;
        };
        return end();
    }
    void print_debug_info() {
        LOG_DEBUG("calling print debug information.");
        LOG_DEBUG("iterating through mempool");
        int i = 0;
        ptrdiff_t dist_begin = 0;
        ptrdiff_t dist_end = 0;
        for (auto it = begin(); it != end(); ++it) {
            auto cb = it.getCurrentBlock();
            auto cb_begin = cb->begin();
            auto cb_end = cb->end();
            dist_begin = std::distance(cb_begin, &*it);
            dist_end = std::distance(&*it, cb_end);
            LOG_DEBUG(
                "item at index: {} address: {:#x} value: {} db: {} de: {}", i,
                reinterpret_cast<std::uintptr_t>(&*it), *it, dist_begin,
                dist_end);
            ++i;
            if (dist_begin < 0) {
                ptrdiff_t block_id = std::distance(_data.begin(), cb);
                LOG_WARN("dist(it, begin) < 0 at index: {} ", i);
                LOG_WARN("block ID: {}", block_id);
            }
            if (dist_end > block_size) {
                ptrdiff_t block_id = std::distance(cb, _data.end());
                LOG_WARN("dist(it, begin) > block_size at index: {} ", i);
                LOG_WARN("block ID: {}", block_id);
            }
        }
    }
};
} // namespace aad
#endif
