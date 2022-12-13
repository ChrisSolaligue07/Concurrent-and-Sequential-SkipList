//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#ifndef SEQUENTIAL_CONCURRENT_SKIPLIST_CNODE_H
#define SEQUENTIAL_CONCURRENT_SKIPLIST_CNODE_H


#include <vector>
#include <mutex>
#include <atomic>

template<class T>
class cnode {
public:
    T key;
    unsigned int top_level;
    std::vector<cnode *> forward;
    bool marked;
    bool f_linked;
    std::mutex n_lock;

    cnode(unsigned int lvl, T key);
    void lock();
    void unlock();
};

template class cnode<int>;
template class cnode<float>;
template class cnode<char>;
template class cnode<double>;
template class cnode<size_t>;

#endif //SEQUENTIAL_CONCURRENT_SKIPLIST_CNODE_H
