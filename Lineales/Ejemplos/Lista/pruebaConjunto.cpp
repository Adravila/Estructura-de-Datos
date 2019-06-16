#include <iostream>
#include "Lista_enla.h"
#include <cstddef>
#include <cstring>

using namespace std;

template <typename T>
class Conjunto
{
public:
    Conjunto();
    bool conjuntoVacio() const;
    void agregarElemento(const T& e);
    void eliminarElemento(const T& e);
    Conjunto<T> Union(const Conjunto<T>& c);
    Conjunto<T> Interseccion(const Conjunto<T>& c);
    Conjunto<T> Diferencia(const Conjunto<T>& c);
    void verConjunto();
private:
    Lista<T>L;
    typename Lista<T>::posicion p;
};

template <typename T>
Conjunto<T>::Conjunto() : L(Lista<T>()) {}

template <typename T>
bool Conjunto<T>::conjuntoVacio() const
{
    p = L.primera();
    return p == L.fin();
}

template <typename T>
void Conjunto<T>::agregarElemento(const T& e)
{
    p = L.fin();
    L.insertar(e,p);
}

template <typename T>
void Conjunto<T>::eliminarElemento(const T& e)
{
    p = L.buscar(e);
    if(p != L.fin())
        L.eliminar(p);
}

template <typename T>
Conjunto<T> Conjunto<T>::Union(const Conjunto<T>& c)
{
    typename Lista<T>::posicion q;
    Conjunto c_new;
    p = L.primera();

    while(p != L.fin())
    {
        c_new.agregarElemento(L.elemento(p));
        p = L.siguiente(p);
    }
    p = c.L.primera();

    while(p != c.L.fin())
    {
        q = L.buscar(c.L.elemento(p));
        if(q == L.fin())
        {
            c_new.agregarElemento(c.L.elemento(p));
        }
        p = c.L.siguiente(p);
    }
    return c_new;
}

template <typename T>
Conjunto<T> Conjunto<T>::Diferencia(const Conjunto<T>& c)
{
    typename Lista<T>::posicion q;
    Conjunto c_new;
    p = L.primera();
    
    while(p != L.fin())
    {
        q = c.L.buscar(L.elemento(p));
        if(q == c.L.fin())
        {
            c_new.agregarElemento(L.elemento(p));
        }
        p = L.siguiente(p);
    }
    return c_new;
}

template <typename T>
Conjunto<T> Conjunto<T>::Interseccion(const Conjunto<T>& c)
{
    typename Lista<T>::posicion q;
    Conjunto c_new;
    p = L.primera();
    
    while(p != L.fin())
    {
        q = c.L.buscar(L.elemento(p));
        if(q != c.L.fin())
        {
            c_new.agregarElemento(L.elemento(p));
        }
        p = L.siguiente(p);
    }
    return c_new;
}

template <typename T>
void Conjunto<T>::verConjunto()
{
    p = L.primera();
    cout << "Conjunto: {";
    while(p != L.fin())
    {
        cout << L.elemento(p) << " ";
        p = L.siguiente(p);
    }
    cout << "}" << endl;
}

int main()
{
    Conjunto<int> c1,c2,c3,c4,c5;
    c1.agregarElemento(1);
    c1.agregarElemento(4);
    c1.agregarElemento(6);
    c1.agregarElemento(8);
    c2.agregarElemento(3);
    c2.agregarElemento(4);
    c2.agregarElemento(5);
    c2.agregarElemento(6);
    c1.verConjunto();
    c2.verConjunto();
    c3 = c1.Union(c2);
    c3.verConjunto();
    c4 = c1.Interseccion(c2);
    c4.verConjunto();
    c5 = c1.Diferencia(c2);
    c5.verConjunto();
}