#include <vector>

template <class T>
Conjunto<T>::Conjunto() : _min(nullptr), _max(nullptr), _num(0), _raiz(0) {
}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res;
    struct Nodo *nodo = _raiz;

    while (nodo != nullptr) {
        T val = nodo->_valor;
        if (clave == val) res = true;
        else if (clave < val) nodo = nodo->_izq;
        else nodo = nodo->_der;
    }
    
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    struct Nodo **ptrDirSiguiente = &(_raiz);
    T* val = &((*ptrDirSiguiente)->_valor);    

    while (*ptrDirSiguiente != nullptr && clave != *val) {
        if (clave < *val) ptrDirSiguiente = &((*nodo)->_izq);
        else ptrDirSiguiente = &((*ptrDirSiguiente)->_der);
        val = &((*ptrDirSiguiente)->_valor);
    }
    // Salimos por llegar al último --> agregamos
    if (*ptrDirSiguiente == nullptr) {   
       struct Nodo nuevo = new Nodo(clave);
        *ptrDirSiguiente = &nuevo;
        if (clave < _min) _min = clave;
        if (!(clave < _max)) _max = clave;
        _num++;
    }
}       

template <class T>
void Conjunto<T>::remover(const T&) {
    assert(false);
}
// Pre {clave:T € conj:Conjunto<T> ^L siguiente(clave):T € conj:Conjunto<T>}
template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    struct Nodo *nodo = &(_raiz);
    T* val = &(nodo->_valor);
    std::vector<Nodo*> stackNodos = vector<Nodo*>();
    T* res;

    // Encontrar el nodo cuyo valor es _clave_
    while (clave != *val) {
        stackNodos.push_back(nodo);
        if (clave < *val) nodo = nodo->_izq;
        else nodo = nodo->_der;
        val = &(nodo->_valor);
    }
    if (nodo->_der != nullptr) {
        nodo = nodo->_der;
        while (nodo->_izq != nullptr) {nodo = nodo->_izq}
        res = &(nodo->_valor);
    } else {
        while (nodo->valor < clave) {nodo = stackNodos.pop_back();}
          res = &(nodo->valor)
    }
    
    return *res;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return _min;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return _max;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _num;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

