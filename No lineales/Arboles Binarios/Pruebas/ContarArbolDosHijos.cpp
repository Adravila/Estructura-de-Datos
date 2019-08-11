
#include <algorithm>
#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

/* Comprueba si el árbol tiene siempre dos hijos o ninguno por cada uno de los nodos de éste */

template <typename T>
int dosHijosRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
    int cont = 0;
    if (Abin<T>::NODO_NULO == n)
        return 0;
    else if ((Abin<T>::NODO_NULO != A.hijoIzqdoB(n) && Abin<T>::NODO_NULO != A.hijoDrchoB(n)) || // Tiene 2 hijos
             (Abin<T>::NODO_NULO == A.hijoIzqdoB(n) && Abin<T>::NODO_NULO == A.hijoDrchoB(n)))   // Es hoja
    {
        ++cont;
    }
    return cont + dosHijosRec(A.hijoIzqdoB(n), A) + dosHijosRec(A.hijoDrchoB(n), A);
}

template <typename T>
int arbolDosHijos(const Abin<T> &A)
{
    return dosHijosRec(A.raizB(), A);
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
