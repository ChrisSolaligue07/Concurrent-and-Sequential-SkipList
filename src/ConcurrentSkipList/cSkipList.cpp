//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#include "cSkipList.h"

template<class T>
cSkipList<T>::cSkipList(size_t max_elements){
    max_lvl = (int) round(log(max_elements) / log(1/0.5)) - 1;
    head = new cnode<T>(max_lvl, std::numeric_limits<T>::min());
    tail = new cnode<T>(max_lvl, std::numeric_limits<T>::max());
    for (int i = 0; i < head->forward.size(); i++) {
        head->forward[i] = tail;
        tail->forward[i] = nullptr;
    }
}

template<class T>
void cSkipList<T>::unlock(std::vector<cnode<T> *> *preds, int highestLocked) {
    for (int level = 0; level <= highestLocked; level++) {
        (*preds)[level]->unlock();
    }
}

template<class T>
bool cSkipList<T>::okToDelete(cnode<T> *candidate, int found) {
    /*
     * Esta función es una ayuda para la función remove.
     * Determinados que el nodo está totalmente enlazado.
     * No debe estar marcado, si lo está es porque debe estar ocupado.
     */
    return (candidate->f_linked && candidate->top_level == found && !candidate->marked);
}

template<class T>
bool cSkipList<T>::find(T key) {

    /*
     * Realiza la búsqueda de un key determinada, para ello se debe determinar si el nodo existe.
     * Por ello se hace uso de la función find ya implementada para este caso.
     * En este caso no devolvemos el valor, solo se requiere saber si este existe o no dentro de la SkipList.
     * En caso de encontrar devuelve (1)
     * Caso contrario devuelve (0)
     */

    std::vector<cnode<T> *> preds(max_lvl + 1, nullptr), succs(max_lvl + 1, nullptr);

    int found = find(key, &preds, &succs);
    if (found == -1) return false;

    cnode<T> *curr = head;
    for (int level = max_lvl; level >= 0; level--) {
        while (curr->forward[level] != nullptr && key > curr->forward[level]->key) {
            curr = curr->forward[level];
        }
    }
    curr = curr->forward[0];

    /*
     * Para obtener la sentencia de manera adecuada se toma en cuenta lo siguiente.
     *  - El nodo debe existir.
     *  - No debe estar marcado.
     *  - Debe estar enlazado.
     */

    if (curr != nullptr && curr->key == key && succs[found]->f_linked && !succs[found]->marked) //  (1)
        return true;
    else
        return false;   //  (0)
}

template<class T>
int cSkipList<T>::find(T searchKey, std::vector<cnode<T> *> *preds, std::vector<cnode<T> *> *succs) {

    /*
     * Encuentra los predecesores y sucesores de donde esté situada la key.
     * En caso esta no exista retorna -1.
     */

    int found = -1;
    cnode<T> *pred = head;

    for (int i = max_lvl; i >= 0; i--) {
        cnode<T> *curr = pred->forward[i];
        while (searchKey > curr->key) {
            pred = curr;
            curr = pred->forward[i];
        }
        if (found == -1 && searchKey == curr->key) {
            found = i;
        }
        (*preds)[i] = pred;
        (*succs)[i] = curr;
    }
    return found;
}

template<class T>
bool cSkipList<T>::insert(T key) {
    //  init
    unsigned int topLevel = randomLevel();
    std::vector<cnode<T> *> preds(max_lvl + 1, nullptr), succs(max_lvl + 1, nullptr);
    //  ..

    while (true) {

        /*
         * Busca la manera de poder insertar el nuevo dato a la SkipList.
         * - found = find ... -> encuentra los predecesores y sucesores de donde se
         *   quiere insertar la nueva key.
         */

        int found = find(key, &preds, &succs);
        if (found != -1) {

            /*
             * Si se encuentra y esta marcado, se espera para poder continuar insertando.
             * Si se encuentra, pero no están marcados, entonces se espera a que estén enlazados
             * para continuar.
             * Si no lo encuentra continua con la inserción.
             */

            cnode<T> *nodeFound = succs[found];
            if (!nodeFound->marked) {
                while (!nodeFound->f_linked);
                return false;
            }
            continue;
        }
        int highestLocked = -1;
        cnode<T> *pred, *succ, *prevPred = nullptr;

        // Comprueba si el predecesor y el sucesor son los mismos de cuando se quiere realizar la operación.
        bool valid = true;

        for (int level = 0; valid && level <= topLevel; level++) {
            pred = preds[level];
            succ = succs[level];
            if (pred != prevPred) {
                pred->lock();
                highestLocked = level;
                prevPred = pred;
            }
            valid = !pred->marked && !succ->marked && pred->forward[level] == succ;
            /*
             * Si el predecesor está marcado o si el predecesor y sucesor cambian,
             * entonces se vuelve a intentar la operación.
            */

        }
        if (!valid) {
            /*
             * No cumple con las condiciones, se sale de la operación e intenta de nuevo.
             * Se desbloquean los nodos.
             */
            unlock(&preds, highestLocked);
            continue;
        }

        // Satisface las condiciones, se crea e inserta el nuevo nodo.
        auto *newNode = new cnode<T>(topLevel, key);

        // Se actualizan los predecesores y sucesores.
        for (int level = 0; level <= topLevel; level++) {
            newNode->forward[level] = succs[level];
            preds[level]->forward[level] = newNode;
        }

        // Se marca el nodo como completamente enlazado.
        newNode->f_linked = true;

        // Como la inserción fue finalizada entonces se procede a desbloquear todos los nodos.
        unlock(&preds, highestLocked);
        return true;
    }
}

template<class T>
bool cSkipList<T>::remove(T key) {
    // init
    cnode<T> *nodeToDelete = nullptr;
    bool isMarked = false;
    int topLevel = -1;
    std::vector<cnode<T> *> preds(max_lvl + 1, nullptr), succs(max_lvl + 1, nullptr);
    // ..

    while (true) {
        // Busca el predecesor y el sucesor de donde se encuentra la key a borrar.
        int found = find(key, &preds, &succs);

        if (isMarked || found != -1 && okToDelete(succs[found], found)) {

            if (!isMarked) {    // Si no está marcado, se bloquea el nodo y se marca para que este sea borrado.
                nodeToDelete = succs[found];
                topLevel = nodeToDelete->top_level;
                nodeToDelete->lock();
                if (nodeToDelete->marked) {
                    nodeToDelete->unlock();
                    return false;
                }
                nodeToDelete->marked = true;
                isMarked = true;
                nodeToDelete->unlock();
            }

            int highestLocked = -1;
            cnode<T> *pred, *succ, *prevPred = nullptr;

            // Comprueba si el predecesor y el sucesor no están marcados para borrar y si el nodo siguiente es el nodo que se quiere borrar
            // o si este ha cambiado.

            bool valid = true;
            for (int level = 0; valid && level <= topLevel; level++) {
                pred = preds[level];
                succ = succs[level];
                if (pred != prevPred) {
                    pred->lock();
                    highestLocked = level;
                    prevPred = pred;
                }
                valid = !pred->marked && pred->forward[level] == succ;
            }

            if (!valid) {

                /*
                 * No cumple con las condiciones, se sale de la operación e intenta de nuevo.
                 * Se desbloquean los nodos.
                */

                unlock(&preds, highestLocked);
                continue;
            }

            // Satisface las condiciones, se elimina el nodo y se vincula con los sucesores adecuadamente.
            for (int level = topLevel; level >= 0; level--) {
                preds[level]->forward[level] = nodeToDelete->forward[level];
            }
            nodeToDelete->unlock();
            // std::free(nodeToDelete);
            // Se completa con la eliminación y se desbloquea los nodos.
            unlock(&preds, highestLocked);
            return true;
        } else
            return false;
    }
}

template<class T>
double cSkipList<T>::get_random_real() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(gen);
}

template<class T>
unsigned int cSkipList<T>::randomLevel() {
    /*
     * Generamos un nivel aleatorio, tal y como menciona el paper
     * este se va a generar dependiendo de una probabilidad P
     * en este caso P es igual a 0.5.
     * Esta implementación de SkipList lo tiene como defecto,
     * pero puede ser cambiada.
     */
    unsigned int newLevel = 0;
    while ( get_random_real() <= 0.5){
        newLevel ++;
    }
    return std::min(newLevel, max_lvl);
}

template<class T>
void cSkipList<T>::print() {
    typedef cnode<T> *nd_p;
    nd_p p = head;
    for (int i = max_lvl; i >= 0; i--) {
        std::cout << "[" << i << "]";
        if (p->forward[i] == nullptr) {
            std::cout << "NIL" << std::endl;
        } else {
            nd_p q = p->forward[i];
            std::cout << "-> ";
            while (q != nullptr && q != tail) {
                std::cout << q->key << " ";
                q = q->forward[i];
            }
            if (q->forward[i] == nullptr) {
                std::cout << "-> NIL" << std::endl;
            }
        }
    }
    std::cout << "-H-" << std::endl;
}