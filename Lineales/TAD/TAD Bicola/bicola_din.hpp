#ifndef BICOLA_DYN_H
#define BICOLA_DYN_H
#include<cassert>

template <typename T> class Bicola {
public:
    Bicola(); // constructor
    Bicola(const Bicola<T>& C); // ctor. de copia
    Bicola<T>& operator =(const Bicola<T>& C); // asignación de colas
    bool vacia() const;
    const T& frente() const;
    const T& culo() const;
    void pop_inicio();
    void pop_fin();
    void push_fin(const T& x);
    void push_inicio(const T& x);
    ~Bicola(); // destructor
private:
    struct nodo {
        T elto;
        nodo* sig;
        nodo(const T& e, nodo* p = 0): elto(e), sig(p) {}
    };
    nodo *inicio, *fin; // extremos de la cola
    void copiar(const Bicola<T>& C);
};

// Método privado
template <typename T>
void Bicola<T>::copiar(const Bicola<T>& C){
    if (C.inicio){ // C no está vacía
        // Copiar el primer elto.
        inicio = fin = new nodo(C.inicio->elto);
        // Copiar el resto de elementos hasta el final de la cola.
        for (nodo *p = C.inicio->sig; p; p = p->sig) {
            fin->sig = new nodo(p->elto);
            fin = fin->sig;
        }
    }
}

template <typename T>
inline Bicola<T>::Bicola() : inicio(0), fin(0) {}

template <typename T>
inline Bicola<T>::Bicola(const Bicola<T>& C) : inicio(0), fin(0){ copiar(C); }

template <typename T>
inline Bicola<T>& Bicola<T>::operator =(const Bicola<T>& C){
    if (this != &C) { // evitar autoasignación
        this->~Bicola(); // vaciar la cola actual
        copiar(C);
    }
    return *this;
}

template <typename T>
inline bool Bicola<T>::vacia() const{ return (inicio == 0); }

template <typename T>
inline const T& Bicola<T>::frente() const{
    assert(!vacia());
    return inicio->elto;
}

template <typename T>
inline const T& Bicola<T>::culo() const{
    assert(!vacia());
    return fin->elto;
}

template <typename T>
inline void Bicola<T>::pop_inicio(){
    assert(!vacia());
    nodo* p = inicio;
    inicio = p->sig;
    if (!inicio)
        fin = 0;
    delete p;
}

template <typename T>
inline void Bicola<T>::pop_fin(){
    assert(!vacia());
    nodo* p = inicio;
    while(p->sig != fin){
       p = p->sig;
    }
    fin = p;
    fin->sig = 0;
    delete p;
}

template <typename T>
inline void Bicola<T>::push_fin(const T& x){
    nodo* p = new nodo(x);
    if (inicio == 0) // cola vacía
        inicio = fin = p;
    else
        fin = fin->sig = p;
}

template <typename T>
inline void Bicola<T>::push_inicio(const T& x){
    inicio = new nodo(x,inicio);
    if(!fin)
		fin = inicio;
}

// Destructor: vacía la cola
template <typename T>
Bicola<T>::~Bicola(){
    nodo* p;
    while (inicio) {
        p = inicio->sig;
        delete inicio;
        inicio = p;
    }
    fin = 0;
}

#endif

