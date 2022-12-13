//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#ifndef SEQUENTIAL_CONCURRENT_SKIPLIST_TESTSTRUCT_H
#define SEQUENTIAL_CONCURRENT_SKIPLIST_TESTSTRUCT_H

#include "./ConcurrentSkipList/cSkipList.h"
#include "./SequentialSkipList//sSkipList.h"
#include "./dataGenerator.h"

// Estructura del Test de insertado concurrente y secuencial -----------------------------------

template <class T>
struct TestInsertConcurrent {
    cSkipList<T> cSl;
    std::vector<T> data;
    TestInsertConcurrent(cSkipList<T> &cSl, std::vector<T> &data) : cSl(cSl), data(data) {};
    void operator() (unsigned int elementos) {
        for (unsigned int i = 0; i < elementos; i++) {
            cSl.insert(data[i]);
        }
    }
};

template <class T>
struct TestInsertSequential {
    sSkipList<T> sSl;
    std::vector<T> data;
    TestInsertSequential(sSkipList<T> &sSl, std::vector<T> &data) : sSl(sSl), data(data) {};
    void operator() (unsigned int elementos) {
        for (unsigned int i = 0; i < elementos; i++) {
            sSl.insert(data[i]);
        }
    }
};

// ---------------------------------------------------------------------------------------------


// Estructura del Test de búsqueda concurrente y secuencial ------------------------------------

template <class T>
struct TestBusquedaConcurrent {
    cSkipList<T> cSl;
    std::vector<T> data;
    TestBusquedaConcurrent(cSkipList<T> &cSl, std::vector<T> &data) : cSl(cSl), data(data) {};
    void operator() (unsigned int elementos) {
        for (unsigned int i = 0; i < elementos; i++) {
            cSl.find(data[i]);
        }
    }
};

template <class T>
struct TestBusquedaSequential {
    sSkipList<T> sSl;
    std::vector<T> data;
    TestBusquedaSequential(sSkipList<T> &sSl, std::vector<T> &data) : sSl(sSl), data(data) {};
    void operator() (unsigned int elementos) {
        for (unsigned int i = 0; i < elementos; i++) {
            sSl.find(data[i]);
        }
    }
};

// ---------------------------------------------------------------------------------------------


// Estructura del Test de borrado concurrente y secuencial -------------------------------------

template <class T>
struct TestBorradoConcurrent {
    cSkipList<T> cSl;
    std::vector<T> data;
    TestBorradoConcurrent(cSkipList<T> &cSl, std::vector<T> &data) : cSl(cSl), data(data) {};
    void operator() (unsigned int elementos) {
        for (unsigned int i = 0; i < elementos; i++) {
            cSl.remove(data[i]);
        }
    }
};

template <class T>
struct TestBorradoSequential {
    sSkipList<T> sSl;
    std::vector<T> data;
    TestBorradoSequential(sSkipList<T> &sSl, std::vector<T> &data) : sSl(sSl), data(data) {};
    void operator() (unsigned int elementos) {
        for (unsigned int i = 0; i < elementos; i++) {
            sSl.remove(data[i]);
        }
    }
};

// ---------------------------------------------------------------------------------------------


#endif //SEQUENTIAL_CONCURRENT_SKIPLIST_TESTSTRUCT_H
