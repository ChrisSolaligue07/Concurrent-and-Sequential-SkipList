//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#include "sSkipList.h"

template<class T>
sSkipList<T>::sSkipList(size_t max_elements)
        : max_lvl((int) round(log(max_elements) / log(1/0.5)) - 1), header(max_lvl, {}), current_lvl(0) {}

template<class T>
bool sSkipList<T>::get_random_bool() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);
    return distribution(gen);
}

template<class T>
unsigned int sSkipList<T>::randomLevel() {
    // si la "moneda" cae cara, el nivel va aumentando, caso contrario no aumenta.
    // Este nivel determinara en que nivel de las LE. se insertara el dato.
    unsigned int level = 0;
    while (get_random_bool() == true && level < max_lvl) level++;
    return level;
}


template<class T>
void sSkipList<T>::print() {
    typedef snode<T> *nd_p;
    using std::cout, std::endl;
    nd_p p = &header;
    for (int i = max_lvl - 1; i >= 0; i--) {
        cout << "[" << i << "] -> ";
        if (p->forward[i] == nullptr) {
            cout << "NIL" << endl;
        } else {
            nd_p q = p->forward[i];
            while (q != nullptr) {
                cout << q->key << " ";
                q = q->forward[i];
            }
            cout << endl;
        }
    }
    cout << "-H-" << endl;
}

template<class T>
snode<T> *sSkipList<T>::find(std::vector<snode<T> *> *prev, T key) {
    prev->resize(max_lvl, nullptr);
    snode<T> *next = &header;
    for (int i = current_lvl - 1; 0 <= i; --i) {
        while (next->forward[i] != nullptr && next->forward[i]->key < key) {
            next = next->forward[i];
        }
        (*prev)[i] = next;
    // [prev] se queda con el valor anterior al que se busca
    // asi mismo almacena los nodos recorridos anteriormente.
    }
    next = next->forward[0];    // obtiene el siguiente número del cual se busca
// [prev] -> [-] -> [next]
    return next;
}

template<class T>
bool sSkipList<T>::find(T key) {
    snode<T> *next = &header;
    for (int i = current_lvl - 1; 0 <= i; --i) {
        while (next->forward[i] != nullptr && next->forward[i]->key < key) {
            next = next->forward[i];
        }
    }
    next = next->forward[0];    // obtiene el siguiente valor del cual se busca
    if (next != nullptr && next->key == key) {
        return true;
    } else return false;
}

template<class T>
bool sSkipList<T>::insert(T key) {
    std::vector<snode<T> *> prev; // vector con los nodos previos al que se quiere insertar
    snode<T> *next = find(&prev, key);    // nodo siguiente al nodo que se quiere insertar
    if (next != nullptr && next->key == key) {
        // si nodo next es diferente de nullptr y la key siguiente es igual de la key a insertar
        // no se inserta nada, retorna false.
        return false;
    } else {
        unsigned int newLevel = randomLevel();
        if (newLevel > current_lvl) {
            for (int i = current_lvl; i < newLevel; i++) {
                prev[i] = &header;
            }
            current_lvl = newLevel;    // Se actualiza el nuevo nivel
            // Si el nuevo nivel que tendrá el nodo a insertar es mayor que el nivel actual de la sSkipList
            // se hace que el nodo prev o antecesor apunte al head.
        }
        auto *new_node = new snode<T>(newLevel, key);    // Generamos un nuevo nodo torré con su respectivo key.
        for (unsigned int i = 0; i < newLevel; ++i) {
            new_node->forward[i] = prev[i]->forward[i];
            prev[i]->forward[i] = new_node;
        }   // Modificación de los punteros.
        return true;
    }
}

template<class T>
bool sSkipList<T>::remove(T key) {
    std::vector<snode<T> *> prev;
    snode<T> *next = find(&prev, key);
    if (next != nullptr && next->key == key) {
        for (int i = 0; i <= current_lvl - 1; i++) {
            if (prev[i]->forward[i] != next)
                break;
            prev[i]->forward[i] = next->forward[i];
        }
        while (current_lvl - 1 > 0 && header.forward[current_lvl - 1] == nullptr) {
            current_lvl--;  // Se decremente hasta que llegue a un nivel adecuado
        }   // Si el nivel actual es diferente de nulo entonces se encuentra en un nivel adecuado.
        return true;
    } else {
        return false;
    }
}
