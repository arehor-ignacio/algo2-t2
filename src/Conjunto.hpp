#include <vector>

template <class T>
Conjunto<T>::Conjunto() : _min(T()), _max(T()), _num(0), _raiz(nullptr) {}

void destruirNodo (struct Nodo* nodo) {
    if (nodo != nullptr) {
        destruirNodo(nodo->_izq);
        destruirNodo(nodo->_der);
        delete nodo;
    }
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruirNodo(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res = false;
    struct Nodo *nodo = _raiz;
    T* val = &(nodo->_valor);

    while (nodo != nullptr && clave != *val) {
        if (clave < *val) nodo = nodo->_izq;
        else nodo = nodo->_der;
        val = &(nodo->_valor);
    }
    
    return nodo != nullptr;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    struct Nodo **ptrDirSiguiente = &(_raiz);
    T* val = &((*ptrDirSiguiente)->_valor);    

    while (*ptrDirSiguiente != nullptr && clave != *val) {
        if (clave < *val) ptrDirSiguiente = &((*ptrDirSiguiente)->_izq);
        else ptrDirSiguiente = &((*ptrDirSiguiente)->_der);
        val = &((*ptrDirSiguiente)->_valor);
    }

    // Cuando salimos del ciclo, tenemos que agregar el elemento

    if (*ptrDirSiguiente == nullptr) {   
       struct Nodo *nuevo = new Nodo(clave);
        *ptrDirSiguiente = nuevo;
        if (clave < *_min) _min = &(nuevo->_valor);
        if (!(clave < *_max)) _max = &(nuevo->_valor);
        _num++;
    }
}       

template <class T>
void Conjunto<T>::remover(const T& clave) {
   struct Nodo **ptrDirSiguiente = &(_raiz);
    T* val = &((*ptrDirSiguiente)->_valor);
    std::vector<Nodo*> padres = std::vector<Nodo*>();

    while ((*ptrDirSiguiente != nullptr) && (clave != *val)) {
        padres.push_back(*ptrDirSiguiente);
        if (clave < *val) ptrDirSiguiente = &((*ptrDirSiguiente)->_izq);
        else ptrDirSiguiente = &((*ptrDirSiguiente)->_der);
    }
    // Si lo encontramos, lo eliminamos. Si no, terminamos.
    if (*ptrDirSiguiente != nullptr) {
        // Es una hoja
        if ((*ptrDirSiguiente)->_izq == nullptr &&
            (*ptrDirSiguiente)->_der == nullptr) {
            struct Nodo* tmpNodo = *ptrDirSiguiente;
            *ptrDirSiguiente = nullptr;
            delete tmpNodo;
        } else if ((*ptrDirSiguiente)->_izq == nullptr ||
                (*ptrDirSiguiente)->_der == nullptr) {
            
        }

        // Actualizamos el minimo y el máximo, independientemente si el nodo que
        // borramos lo era o no.

        actualizarMinMax();

        // if ((*ptrDirSiguiente)->_izq == nullptr) // Encontrar sucesor
        // else // Encontrar predecesor
        //     //ambas funciones pueden devolver null, de esa manera contempalmos
        //     el caso en que sea una hoja. También tenemos que eliminar limpiar
        //     el puntero al hijo del que puenteamos.

    }
}
// Pre {clave:T € conj:Conjunto<T> ^L siguiente(clave):T € conj:Conjunto<T>}
template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    struct Nodo *nodo = _raiz;
    T* val = &(nodo->_valor);
    std::vector<Nodo*> stackNodos = std::vector<Nodo*>();
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
        while (nodo->_izq != nullptr) {nodo = nodo->_izq;}
        res = &(nodo->_valor);
    } else {
        while (nodo->_valor < clave) {
            nodo = stackNodos.back();
            stackNodos.pop_back();
        }
          res = &(nodo->_valor);
    }
    
    return *res;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return *_min;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return *_max;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _num;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

