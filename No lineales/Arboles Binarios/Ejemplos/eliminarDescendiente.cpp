#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

template <typename T>
void encontrarHijo(Abin<T> &A, typename Abin<T>::nodo n)
{
    if (n != Abin<T>::NODO_NULO)
    {
        if((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) || 
        (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
        {
            eliminarDescendientes(A,n);
        }
        else
        {
            encontrarHijo(A,A.hijoIzqdoB(n));
            encontrarHijo(A,A.hijoDrchoB(n));
        }
    }
}

template <typename T>
void eliminarDescendientes(Abin<T> &A, typename Abin<T>::nodo n)
{
    if (n != Abin<T>::NODO_NULO)
    {
        eliminarDescendientes(A,A.hijoIzqdoB(n));
        eliminarDescendientes(A,A.hijoDrchoB(n));
        if(A.hijoIzqdoB(n) != Abin<T>::NODO_NULO)
        {
            A.eliminarHijoIzqdoB(n);
        }
        if(A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
        {
            A.eliminarHijoDrchoB(n);
        }
    }
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
    Abin<tElto> A;
    cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    ifstream fe("abin.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);              // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); // en std::cout

    encontrarHijo(A, A.raizB());

    imprimirAbin(A); // en std::cout

    //cout << "\nCantidad de nodos con tres nietos: " << encontrarHijo(A, A.raizB()) << endl;
}