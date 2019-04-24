#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Contar el número de nodos pares de todo el árbol general
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
int numHijos(typename Agen<T>::nodo n, const Agen<T> &A)
{
    int nHijos;
    typename Agen<T>::nodo hijo;
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        nHijos = 0;
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            ++nHijos;
            hijo = A.hermDrcho(hijo);
        }
        return nHijos;
    }
}

template <typename T>
int contarNodosPadresRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int cont = 0;
        if (numHijos(n, A) % 2 == 0)
        {
            ++cont;
        }
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            cont += contarNodosPadresRec(hijo, A);
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

template <typename T>
int contarNodosPadres(const Agen<T> &A)
{
    return contarNodosPadresRec(A.raiz(), A);
}

int main()
{
    Agen<char> A, B, C, D;
    cout << "\n*** Lectura de árbol general A de agen.dat ***\n";
    ifstream fa("Data/agen.dat"); // abrir fichero de entrada
    rellenarAgen(fa, A);     // desde fichero
    fa.close();
    cout << "\n*** Mostrar árbol general A ***\n";
    imprimirAgen(A); // en std::cout
    cout << "\nNúmero de nodos pares del árbol A 'agen': " << contarNodosPadres(A) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);         // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nNúmero de nodos pares del árbol B 'agen-ter': " << contarNodosPadres(B) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);         // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nNúmero de nodos pares del árbol C 'agen-cua': " << contarNodosPadres(C) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);         // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nNúmero de nodos pares del árbol D 'agen-abu': " << contarNodosPadres(D) << endl;
}