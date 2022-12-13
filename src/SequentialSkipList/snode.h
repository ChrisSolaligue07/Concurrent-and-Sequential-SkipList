//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#ifndef SEQUENTIAL_CONCURRENT_SKIPLIST_SNODE_H
#define SEQUENTIAL_CONCURRENT_SKIPLIST_SNODE_H

#include <iostream>
#include <random>
#include <vector>

template<class T>
struct snode {
    std::vector<snode *> forward;
    T key; //  key
    snode(int lvl, const T &key);
};

template class snode<int>;
template class snode<float>;
template class snode<char>;
template class snode<double>;
template class snode<size_t>;

#endif //SEQUENTIAL_CONCURRENT_SKIPLIST_SNODE_H
