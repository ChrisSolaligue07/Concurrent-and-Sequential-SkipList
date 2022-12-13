//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#ifndef SEQUENTIAL_CONCURRENT_SKIPLIST_CSKIPLIST_H
#define SEQUENTIAL_CONCURRENT_SKIPLIST_CSKIPLIST_H

#include <vector>
#include <climits>
#include <random>
#include <iostream>
#include "cnode.h"

template <class T>
class cSkipList {
public:
    unsigned int max_lvl;
    explicit cSkipList(size_t max_elements);
    bool remove(T key);
    bool insert(T key);
    bool find(T key);
    void print();
private:
    cnode<T> *head;
    cnode<T> *tail;
    int find(T searchKey, std::vector<cnode<T>*> *preds, std::vector<cnode<T>*> *succs);
    bool okToDelete(cnode<T>* candidate, int found);
    void unlock(std::vector<cnode<T>*> *preds, int highestLocked);
    double get_random_real();
    unsigned int randomLevel();
};

template class cSkipList<int>;
template class cSkipList<float>;
template class cSkipList<char>;
template class cSkipList<double>;
template class cSkipList<unsigned long long int>;



#endif //SEQUENTIAL_CONCURRENT_SKIPLIST_CSKIPLIST_H
