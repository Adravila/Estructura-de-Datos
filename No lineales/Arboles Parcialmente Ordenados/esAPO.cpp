#include <iostream>
#include <fstream>
#include "Cabeceras/abin_din.hpp"
#include "Cabeceras/abin_E-S.h"

using namespace std;

template <typename T>
bool sonDescendientes(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        bool desciende = true;
        if (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO)
        {
            if (A.elemento(n) >= A.elemento(A.hijoIzqdoB(n)))
            {
                desciende = false;
            }
        }
        if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
        {
            if (A.elemento(n) >= A.elemento(A.hijoDrchoB(n)))
            {
                desciende = false;
            }
        }
        return desciende && sonDescendientes(A.hijoIzqdoB(n), A) && sonDescendientes(A.hijoDrchoB(n), A);
    }
}

template <typename T>
bool RamaIzqd(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return true;
    else
    {
        bool completo = true;
        if (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO)
        {
            if (A.hijoDrchoB(n) == Abin<T>::NODO_NULO)
            {
                completo = false;
            }
        }
        else if ((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) || (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
        {
            completo = false;
        }
        return completo && RamaIzqd(A.hijoIzqdoB(n), A) && RamaIzqd(A.hijoDrchoB(n), A);
    }
}

template <typename T>
bool RamaDrch(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        bool completo = true;
        if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
        {
            if (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO)
            {
                completo = false;
            }
        }
        else if ((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) || (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
        {
            completo = false;
        }
        return completo && RamaDrch(A.hijoDrchoB(n), A) && RamaDrch(A.hijoIzqdoB(n), A);
    }
}

template <typename T>
bool esCompleto(typename Abin<T>::nodo n, const Abin<T> &A)
{
    return RamaIzqd(A.hijoIzqdoB(n), A) && RamaDrch(A.hijoDrchoB(n), A);
}

template <typename T>
bool esAPO(const Abin<T> &A)
{
    cout << "\nÁrbol completo: ";
    esCompleto(A.raizB(), A) ? cout << "SÍ" << endl : cout << "NO" << endl;
    cout << "Son descendientes: ";
    sonDescendientes(A.raizB(), A) ? cout << "SÍ" << endl : cout << "NO" << endl;

    return esCompleto(A.raizB(), A) && sonDescendientes(A.raizB(), A);
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
    Abin<tElto> A;
    cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    ifstream fe("Data/abin_3.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);                   // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario A 'abin-completo.data' ***\n";
    imprimirAbin(A); // en std::cout
    cout << "\n¿Es esto un APO?: ";
    esAPO(A) ? cout << "SÍ, es un APO" << endl : cout << "NO, no es un APO" << endl;
}