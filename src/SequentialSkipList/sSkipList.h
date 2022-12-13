//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#ifndef SEQUENTIAL_CONCURRENT_SKIPLIST_SSKIPLIST_H
#define SEQUENTIAL_CONCURRENT_SKIPLIST_SSKIPLIST_H

#include "snode.h"

template<class T>
class sSkipList {
public:
    int max_lvl;            // n
    explicit sSkipList(size_t max_elements);
    bool find(T key);
    bool insert(T key);
    bool remove(T key);
    void print();
private:
    bool get_random_bool();
    unsigned int randomLevel();
    snode<T>* find(std::vector<snode<T> *> *prev, T key);
    snode<T> header;  // header(max_lvl, key={}})
    int current_lvl;        // 1
};

template class sSkipList<int>;
template class sSkipList<float>;
template class sSkipList<char>;
template class sSkipList<double>;
template class sSkipList<size_t>;

#endif //SEQUENTIAL_CONCURRENT_SKIPLIST_SSKIPLIST_H
