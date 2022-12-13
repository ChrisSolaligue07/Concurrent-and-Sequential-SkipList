//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#include "cnode.h"


template<class T>
cnode<T>::cnode(unsigned int lvl, T key): key(key), top_level(lvl), marked(false), f_linked(false),
                                        forward(lvl + 1, nullptr) {};

template<class T>
void cnode<T>::lock() { n_lock.lock(); }

template<class T>
void cnode<T>::unlock() { n_lock.unlock(); }
