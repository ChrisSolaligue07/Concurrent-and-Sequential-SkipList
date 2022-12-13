//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#ifndef SEQUENTIAL_CONCURRENT_SKIPLIST_DATAGENERATOR_H
#define SEQUENTIAL_CONCURRENT_SKIPLIST_DATAGENERATOR_H

#include <vector>
#include <random>

template<class T>
struct randomData {
    int min;
    unsigned int max, tElementos;

    randomData(int min, unsigned int max, unsigned int tElementos);

    randomData(int min, int max);

    int getRandom();

    void generate(std::vector<T> &);
};

template<class T>
randomData<T>::randomData(int min, unsigned int max, unsigned int tElementos): min(min), max(max),
                                                             tElementos(tElementos) {};

template<class T>
randomData<T>::randomData(int min, int max) : min(min), max(max), tElementos(0) {};

template<class T>
void randomData<T>::generate(std::vector<T> &data) {
    for (int i = 0; i < tElementos; i++) {
        data.insert(data.begin() + i, getRandom());
    }
}

template<class T>
int randomData<T>::getRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> distribution(min, max);
    return distribution(gen);
}


#endif //SEQUENTIAL_CONCURRENT_SKIPLIST_DATAGENERATOR_H
