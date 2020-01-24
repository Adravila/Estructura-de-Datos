#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Implementa un subprograma que devuelva el porcentaje de descendientes propios de un árbol general que sean múltiplos de 3
 * Creado por: Adrián Dávila Guerra ©
 * 18/01/2020
**/

template <typename T>
int contarNodos(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        int cont = 0;

        while (hijo != Agen<T>::NODO_NULO)
        {
            cont += 1 + contarNodos(hijo, A);
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

template <typename T>
int descientesPropiosRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        bool multiplo = false;
        int val = 0;

        if (A.elemento(n) % 3 == 0)
        {
            multiplo = true;
        }

        while (hijo != Agen<T>::NODO_NULO)
        {
            if (multiplo)
            {
                val += 1;
            }
            val += descientesPropiosRec(hijo, A);
            hijo = A.hermDrcho(hijo);
        }
        return val;
    }
}

template <typename T>
float descientesPropios(typename Agen<T>::nodo n, const Agen<T> &A)
{
    int cont = contarNodos(n, A);
    int mult = descientesPropiosRec(n, A);
    return (float) mult / (float) cont;
}

int main()
{
    Agen<char> A, B, C, D;
    cout << "\n*** Lectura de árbol general A de agen.dat ***\n";
    ifstream fa("Data/agen_mult3.dat"); // abrir fichero de entrada
    rellenarAgen(fa, A);          // desde fichero
    fa.close();
    cout << "\n*** Mostrar árbol general A ***\n";
    imprimirAgen(A); // en std::cout
    cout << "\nCalcular porcentaje de descendientes propios múltiplo 3 del árbol A 'agen': " << descientesPropios(A.raiz(), A) << endl;
}
