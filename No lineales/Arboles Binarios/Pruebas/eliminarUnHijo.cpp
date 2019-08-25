#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

template <typename T>
void procesarElim(typename Abin<T>::nodo n, Abin<T> &A)
{
    if (Abin<T>::NODO_NULO != n)
    {
        procesarElim(A.hijoIzqdoB(n), A);
        procesarElim(A.hijoDrchoB(n), A);
        if (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO)
        {
            A.eliminarHijoIzqdoB(n);
        }
        if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
        {
            A.eliminarHijoDrchoB(n);
        }
    }
}

template <typename T>
void eliminarUnHijoRec(typename Abin<T>::nodo n, Abin<T> &A)
{
    if (Abin<T>::NODO_NULO != n)
    {
        if ((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) ||
            (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
        {
            procesarElim(n,A);
        }
        else
        {
            eliminarUnHijoRec(A.hijoIzqdoB(n), A);
            eliminarUnHijoRec(A.hijoDrchoB(n), A);
        }
    }
}

template <typename T>
void eliminarUnHijo(Abin<T> &A)
{
    if(!A.arbolVacioB())
    {
        eliminarUnHijoRec(A.raizB(),A);
    }
}

int main()
{
    Abin<char> A;
    cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    ifstream fe("abin.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);     // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); // en std::cout
    eliminarUnHijo(A);
    imprimirAbin(A); // en std::cout

}