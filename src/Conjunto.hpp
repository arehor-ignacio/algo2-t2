
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _size(0) {
}

template <class T>
Conjunto<T>::~Conjunto() {
    eliminarNodo(this->_raiz);
}

template<class T>
void Conjunto<T>::eliminarNodo(Conjunto::Nodo* pNodo) {
    if (pNodo != nullptr) {
        eliminarNodo(pNodo->izq);
        eliminarNodo(pNodo->der);
        delete pNodo;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    struct Nodo* nodoArbol = this->_raiz;
    while (nodoArbol != nullptr && nodoArbol->valor != clave) {
        if (clave < nodoArbol->valor) nodoArbol = nodoArbol->izq;
        else nodoArbol = nodoArbol->der;
    }
    return nodoArbol != nullptr;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    struct Nodo** pDirNodo = &(this->_raiz);
    while (*pDirNodo != nullptr && (*pDirNodo)->valor != clave){
        if (clave < (*pDirNodo)->valor) pDirNodo = &((*pDirNodo)->izq);
        else pDirNodo = &((*pDirNodo)->der);
    }
    if (*pDirNodo == nullptr) {
        *pDirNodo = new Nodo(clave);
        this->_size++;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    struct Nodo** pDirNodo = &(this->_raiz);
    this->_size--;
    while ((*pDirNodo)->valor != clave) {
        if (clave < (*pDirNodo)->valor) pDirNodo = &((*pDirNodo)->izq);
        else pDirNodo = &((*pDirNodo)->der);
    }
    if (esHoja(*pDirNodo)) {
        delete *pDirNodo;
        *pDirNodo = nullptr;
    }
    else if ((*pDirNodo)->izq == nullptr && (*pDirNodo)->der != nullptr) {
        struct Nodo* hijoDer = (*pDirNodo)->der;
        delete *pDirNodo;
        *pDirNodo = hijoDer;
    }
    else if ((*pDirNodo)->der == nullptr && (*pDirNodo)->izq != nullptr) {
        struct Nodo* hijoIzq = (*pDirNodo)->izq;
        delete *pDirNodo;
        *pDirNodo = hijoIzq;
    }
    else {
        struct Nodo** pNodo = &((*pDirNodo)->izq);
        while ((*pNodo)->der != nullptr) {
            pNodo = &((*pNodo)->der);
        }
        struct Nodo* pPred = *pNodo;
        *pNodo = (*pNodo)->izq;

        pPred->izq = (*pDirNodo)->izq;
        pPred->der = (*pDirNodo)->der;
        delete *pDirNodo;
        *pDirNodo = pPred;

    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    struct Nodo* pNodo = this->_raiz;
    std::stack<struct Nodo*> padres = std::stack<struct Nodo*>();
    while (pNodo->valor != clave) {
        padres.push(pNodo);
        if (clave < pNodo->valor) pNodo = pNodo->izq;
        else pNodo = pNodo->der;
    }
    if (pNodo->der != nullptr) {
        pNodo = pNodo->der;
        while (pNodo->izq != nullptr) {
            pNodo = pNodo->izq;
        }
        return pNodo->valor;
    } else {
        while (pNodo != padres.top()->izq) {
            pNodo = padres.top();
            padres.pop();
        }
        return padres.top()->valor;
    }
}

template <class T>
const T& Conjunto<T>::minimo() const {
    struct Nodo* pNodo = this->_raiz;
    while (pNodo->izq != nullptr) {
        pNodo = pNodo->izq;
    }
    return pNodo->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    struct Nodo* pNodo = this->_raiz;
    while (pNodo->izq != nullptr) {
        pNodo = pNodo->der;
    }
    return pNodo->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_size;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template<class T>
bool Conjunto<T>::esHoja(struct Nodo* pNodo) {
    return (pNodo == nullptr || (pNodo->izq == nullptr && pNodo->der == nullptr));
}
