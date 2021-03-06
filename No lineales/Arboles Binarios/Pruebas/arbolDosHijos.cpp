
#include <algorithm>
#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

/* Comprueba si el árbol tiene siempre dos hijos o ninguno por cada uno de los nodos de éste */

template <typename T>
bool arbolDosHijosRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else if ((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) ||
             (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
    {
        return false;
    }
    else
    {
        return arbolDosHijosRec(A, A.hijoIzqdoB(n)) && arbolDosHijosRec(A, A.hijoDrchoB(n));
    }
}

template <typename T>
bool arbolDosHijos(const Abin<T> &A)
{
    return arbolDosHijosRec(A, A.raizB());
}

using namespace std;

int main()
{
    Abin<char> A;
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("abin-2.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);     // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(A); // en std::cout
    cout << "Este árbol contiene por cada nodo dos hijos o ninguno: " << arbolDosHijos(A) << endl;
}
