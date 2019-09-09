#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Comprobar si el árbol contiene un nodo que sea nieto y abuelo a la vez
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
bool esAbuelo(typename Agen<T>::nodo n, int prof, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        bool res = false;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        if (prof == 2)
        {
            res = true;
        }
        while (hijo != Agen<T>::NODO_NULO && !res)
        {
            res = esAbuelo(hijo, prof + 1, A);
            hijo = A.hermDrcho(hijo);
        }
        return res;
    }
}

template <typename T>
bool esNieto(typename Agen<T>::nodo n, const Agen<T> &A)
{
    return n != Agen<T>::NODO_NULO && A.padre(n) != Agen<T>::NODO_NULO && A.padre(A.padre(n)) != Agen<T>::NODO_NULO;
}

template <typename T>
bool esNietoAbuelo(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        bool res = false;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        if (esAbuelo(n, 0, A) && esNieto(n,A))
        {
            res = true;
        }
        while (hijo != Agen<T>::NODO_NULO && !res)
        {
            res = esNietoAbuelo(hijo, A);
            hijo = A.hermDrcho(hijo);
        }
        return res;
    }
}

int main()
{
    Agen<char> A;
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fe, A);              // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol general A ***\n";
    imprimirAgen(A);
    cout << "Este árbol tiene un nieto y a su vez es abuelo: ";
    if (esNietoAbuelo(A.raiz(), A))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }
}