//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#include "snode.h"

template<class T>
snode<T>::snode(int lvl, const T &key) : key(key), forward(lvl, nullptr) {}