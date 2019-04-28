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
bool esAbuelo(typename Agen<T>::nodo n, const Agen<T> &A, int prof)
{
    typename Agen<T>::nodo hijo;
    if (n == Agen<T>::NODO_NULO)
        return false;
    else
    {
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            if (esAbuelo(hijo, A, prof + 1))
            {
                // Puede dar tres casos:
                // 1. Que el nodo es nulo (línea 20) y por tanto es falso, no entra en la condición
                // 2. Que el nodo es válido (línea 36) pero no tiene la altura para ser 'abuelo'
                // 3. Que el nodo es válido (línea 36) pero tiene la altura exacta para ser 'abuelo'
                return true;
            }
            hijo = A.hermDrcho(hijo);
        }
        return (prof == 2);
    }
}

template <typename T>
bool esNieto(typename Agen<T>::nodo n, const Agen<T> &A)
{
    int cont = 0;
    while (n != A.raiz())
    {
        ++cont;
        n = A.padre(n);
    }
    return cont == 2;
}

template <typename T>
bool esNietoAbuelo(typename Agen<T>::nodo n, const Agen<T> &A)
{
    return esAbuelo(n, A, 0) && esNieto(n, A);
}

int main()
{
    Agen<char> A;
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fe, A);         // desde fichero
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