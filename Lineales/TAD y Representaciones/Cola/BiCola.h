#ifndef BICOLA_ENLA_H
#define BICOLA_ENLA_H
#include <cassert>

template <typename T> class Bicola {
public:
    Bicola(); // constructor
    Bicola(const Bicola<T>& B); // ctor. de copia
    Bicola<T>& operator =(const Bicola<T>& B); // asignación de colas
    bool vacia() const;
    const T& frente() const;
    const T& trasera() const;
    void pop_f();
    void pop_t();
    void push_f(const T& x);
    void push_t(const T& x);
    ~Bicola(); // destructor

private:
    struct nodo {
        T elto;
        nodo* sig;
        nodo(const T& e, nodo* p = 0): elto(e), sig(p) {}
    };

    nodo *inicio, *fin; // extremos de la cola

    void copiar(const Bicola<T>& B);
};

// Método privado
template <typename T>
void Bicola<T>::copiar(const Bicola<T>& B)
{
    if (B.inicio) { // C no está vacía
        // Copiar el primer elto.
        inicio = fin = new nodo(B.inicio->elto);
        // Copiar el resto de elementos hasta el final de la cola.
        for (nodo *p = B.inicio->sig; p; p = p->sig) {
            fin->sig = new nodo(p->elto);
            fin = fin->sig;
        }
    }
}

template <typename T>
inline Bicola<T>::Bicola() : inicio(0), fin(0) {}

template <typename T>
inline Bicola<T>::Bicola(const Bicola<T>& B) : inicio(0), fin(0)
{
copiar(B);
}

template <typename T>
inline Bicola<T>& Bicola<T>::operator =(const Bicola<T>& B)
{
    if (this != &B) { // evitar autoasignación
        this->~Bicola(); // vaciar la cola actual
        copiar(B);
    }
    return *this;
}

template <typename T>
inline bool Bicola<T>::vacia() const
{
    return (inicio == 0);
}

template <typename T>
inline const T& Bicola<T>::frente() const
{
    assert(!vacia());
    return inicio->elto;
}

template <typename T>
inline const T& Bicola<T>::trasera() const
{
    assert(!vacia());
    return fin->elto;
}

template <typename T>
inline void Bicola<T>::pop_f()
{
    assert(!vacia());
    nodo* p = inicio;
    inicio = p->sig;
    if (!inicio) fin = 0;
        delete p;
}

template <typename T>
inline void Bicola<T>::pop_t()
{
    assert(!vacia());
    nodo* q = inicio;
    while(q->sig!=fin){q=q->sig;}
    delete fin;
    fin = q;
}

template <typename T>
inline void Bicola<T>::push_f(const T& x)
{
    nodo* p = new nodo(x);
    if (inicio == 0) // cola vacía
        inicio = fin = p;
    else
        fin = fin->sig = p;
}

template <typename T>
inline void Bicola<T>::push_t(const T& x)
{
    if(vacia())
        inicio=fin=new nodo(x);
    else{
        nodo* q= inicio;
        inicio = new nodo(x,q);
    }
}

// Destructor: vacía la cola
template <typename T>
Bicola<T>::~Bicola()
{
    nodo* p;
    while (inicio) {
        p = inicio->sig;
        delete inicio;
        inicio = p;
    }
    fin = 0;
}

#endif // BICOLA_ENLA_H
