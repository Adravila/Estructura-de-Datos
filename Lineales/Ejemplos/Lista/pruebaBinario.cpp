#include <iostream>
#include "Lista_enla.h"
#include <cstddef>
#include <cstring>

using namespace std;

template <typename T>
class Binario
{
public:
    Binario(const char *c);
    Binario() {}
    void desplazarBitsIzqd(unsigned int n);
    void desplazarBitsDrch(unsigned int n);
    void mostrarBinario();
    Binario<T> AND(const Binario<T> &b);
    Binario<T> XOR(const Binario<T> &b);
    Binario<T> OR(const Binario<T> &b);
    Binario<T> NOT();

private:
    Lista<T> L;
    typename Lista<T>::posicion p;
};

template <typename T>
Binario<T> Binario<T>::NOT()
{
    p = L.primera();
    while(p != L.fin())
    {
        if(L.elemento(p) == '1')
        {
            L.elemento(p) = '0';
        }
        else
        {
            L.elemento(p) = '1';
        }
        p = L.siguiente(p);
    }
    return *this;
}

template <typename T>
Binario<T> Binario<T>::AND(const Binario &b)
{
    Binario B;
    Lista<T> L1 = L, L2 = b.L, L3 = B.L;
    typename Lista<T>::posicion q, r;
    p = L1.primera();
    q = L2.primera();
    r = L3.primera();
    while (p != L1.fin() && q != L2.fin())
    {
        if (L1.elemento(p) == L2.elemento(q) && L1.elemento(p) == '1')
        {
            L3.insertar('1', r);
        }
        else
        {
            L3.insertar('0', r);
        }
        p = L1.siguiente(p);
        q = L2.siguiente(q);
        r = L3.siguiente(r);
    }
    // Si falta por rellenar L1...
    while (p != L1.fin())
    {
        // Como es un AND y el resto de elementos son nulos, es decir, 0s, entonces rellenar con ceros
        L3.insertar('0', r);
        p = L1.siguiente(p);
        r = L3.siguiente(r);
    }
    // Si falta por rellenar L2...
    while (q != L2.fin())
    {
        // Como es un AND y el resto de elementos son nulos, es decir, 0s, entonces rellenar con ceros
        L3.insertar('0', r);
        q = L2.siguiente(q);
        r = L3.siguiente(r);
    }
    B.L = L3;
    return B;
}

template <typename T>
Binario<T> Binario<T>::OR(const Binario &b)
{
    Binario B;
    Lista<T> L1 = L, L2 = b.L, L3 = B.L;
    typename Lista<T>::posicion q, r;
    p = L1.primera();
    q = L2.primera();
    r = L3.primera();
    while (p != L1.fin() && q != L2.fin())
    {
        if (L1.elemento(p) == L2.elemento(q) && L1.elemento(p) == '0' && L2.elemento(p) == '0')
        {
            L3.insertar('0', r);
        }
        else
        {
            L3.insertar('1', r);
        }
        p = L1.siguiente(p);
        q = L2.siguiente(q);
        r = L3.siguiente(r);
    }
    // Si falta por rellenar L1...
    while (p != L1.fin())
    {
        if (L1.elemento(p) == '1')
            L3.insertar('1', r);
        else
            L3.insertar('0', r);
        p = L1.siguiente(p);
        r = L3.siguiente(r);
    }
    // Si falta por rellenar L2...
    while (q != L2.fin())
    {
        if (L2.elemento(q) == '1')
            L3.insertar('1', r);
        else
            L3.insertar('0', r);
        q = L2.siguiente(q);
        r = L3.siguiente(r);
    }
    B.L = L3;
    return B;
}

template <typename T>
Binario<T> Binario<T>::XOR(const Binario &b)
{
    Binario B;
    Lista<T> L1 = L, L2 = b.L, L3 = B.L;
    typename Lista<T>::posicion q, r;
    p = L1.primera();
    q = L2.primera();
    r = L3.primera();
    while (p != L1.fin() && q != L2.fin())
    {
        if (L1.elemento(p) != L2.elemento(q) ||
            (L1.elemento(p) == '1' && L2.elemento(p) == '0') ||
            (L1.elemento(p) == '0' && L2.elemento(p) == '1'))
        {
            L3.insertar('1', r);
        }
        else
        {
            L3.insertar('0', r);
        }
        p = L1.siguiente(p);
        q = L2.siguiente(q);
        r = L3.siguiente(r);
    }
    // Si falta por rellenar L1...
    while (p != L1.fin())
    {
        if (L1.elemento(p) == '1')
            L3.insertar('1', r);
        else
            L3.insertar('0', r);
        p = L1.siguiente(p);
        r = L3.siguiente(r);
    }
    // Si falta por rellenar L2...
    while (q != L2.fin())
    {
        if (L2.elemento(q) == '1')
            L3.insertar('1', r);
        else
            L3.insertar('0', r);
        q = L2.siguiente(q);
        r = L3.siguiente(r);
    }
    B.L = L3;
    return B;
}

template <typename T>
Binario<T>::Binario(const char *c)
{
    int n = strlen(c);
    p = L.primera();
    for (int i = 0; i < n; ++i)
    {
        L.insertar(c[i], p);
        p = L.siguiente(p);
    }
}

template <typename T>
void Binario<T>::desplazarBitsIzqd(unsigned int n)
{
    assert(L.primera() != L.fin());
    while (n > 0)
    {
        L.insertar('0', L.fin());
        L.eliminar(L.primera());
        --n;
    }
}

template <typename T>
void Binario<T>::desplazarBitsDrch(unsigned int n)
{
    assert(L.primera() != L.fin());
    while (n > 0)
    {
        L.insertar('0', L.primera());
        L.eliminar(L.anterior(L.fin()));
        --n;
    }
}

template <typename T>
void Binario<T>::mostrarBinario()
{
    assert(L.primera() != L.fin());
    p = L.primera();
    while (p != L.fin())
    {
        cout << L.elemento(p);
        p = L.siguiente(p);
    }
    cout << endl;
}

int main()
{
    Binario<char> b1("10101010101"), b2("1010110110"), b3("10110101"), b4("1110101"), b5("111101111");
    cout << "B1: ";
    b1.mostrarBinario();
    b1.desplazarBitsIzqd(5);
    b1.desplazarBitsDrch(2);
    cout << "B1: ";
    b1.mostrarBinario();
    cout << "B3: ";
    b3.mostrarBinario();
    cout << "B5: ";
    b5.mostrarBinario();
    b3 = b3.OR(b5);
    cout << "B3 OR B5: ";
    b3.mostrarBinario();
    b3 = b3.NOT();
    b3.mostrarBinario();
}