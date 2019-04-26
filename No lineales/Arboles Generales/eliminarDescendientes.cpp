#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Eliminar descendientes de un nodo a partir del árbol general
 * Creado por: Adrián Dávila Guerra ©
 * 26/04/2019
**/

template <typename T>
void eliminarDescendientesRec(typename Agen<T>::nodo n, Agen<T> &A)
{
    if (n != Agen<T>::NODO_NULO)
    {
        if (A.hijoIzqdo(n) != Agen<T>::NODO_NULO)
        {
            typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
            while (hijo != Agen<T>::NODO_NULO)
            {
                eliminarDescendientesRec(hijo,A);
                A.eliminarHijoIzqdo(n);
                hijo = A.hermDrcho(hijo);
            }
        }
    }
}

template <typename T>
void eliminarDescendientes(Agen<T> &A)
{
    eliminarDescendientesRec(A.hermDrcho(A.hijoIzqdo(A.raiz())), A);
}

int main()
{
    Agen<char> A;
    cout << "\n*** Lectura de árbol general A de agen.dat ***\n";
    ifstream fa("Data/agen.dat"); // abrir fichero de entrada
    rellenarAgen(fa, A);          // desde fichero
    fa.close();
    cout << "\n*** Mostrar árbol general A ***\n";
    imprimirAgen(A); // en std::cout
    eliminarDescendientes(A);
    cout << endl << "Arbol modificado: " << endl;
    imprimirAgen(A); // en std::cout
}