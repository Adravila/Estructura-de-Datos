#include <algorithm>
#include <iostream>
#include <fstream>
#include "abin_vec_0.hpp"
#include "abin_E-S.h"

/**
template <typename T>
int diferenciaAlturaRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
    {
        return abs(A.alturaB(A.hijoIzqdoB(n)) - A.alturaB(A.hijoDrchoB(n)));
    }
}

template <typename T>
int diferenciaAltura(const Abin<T> &A)
{
    if (!A.arbolVacioB())
    {
        return std::max(diferenciaAlturaRec(A.hijoIzqdoB(A.raizB()),A), diferenciaAlturaRec(A.hijoDrchoB(A.raizB()),A));
    }
    else
    {
        return 0;
    }
}
**/

template <typename T>
int maxDesequilibrio(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
    {
        return std::max(std::max(abs(A.alturaB(A.hijoIzqdoB(n)) - A.alturaB(A.hijoDrchoB(n))), maxDesequilibrio(A.hijoIzqdoB(n),A)), maxDesequilibrio(A.hijoDrchoB(n),A));
    }
}

template <typename T>
int diferenciaAltura(const Abin<T> &A)
{
    return maxDesequilibrio(A.raizB(),A);
}

using namespace std;

int main()
{
    Abin<char> A(16);
    cout << "\n*** Lectura de árbol binario B de abin-2.dat ***\n";
    ifstream fe("abin.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);     // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(A); // en std::cout
    cout << "Altura de un árbol: " << diferenciaAltura(A) << endl;
}
