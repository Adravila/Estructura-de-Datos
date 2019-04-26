#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Calcular la altura mínima del árbol a partir de la raíz
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
int alturaNodo(const Agen<T> &A, typename Agen<T>::nodo n)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        // Declaración de variables
        int alturaMax;
        typename Agen<T>::nodo hijo;
        // Definición de variables
        alturaMax = 0;
        hijo = A.hijoIzqdo(n);
        
        while (hijo != Agen<T>::NODO_NULO)
        {
            alturaMax = max(alturaMax, alturaNodo(A, hijo) + 1);
            hijo = A.hermDrcho(hijo);
        }
        return alturaMax;
    }
}

template <typename T>
int alturaMinArbolRec(const Agen<T> &A, typename Agen<T>::nodo n)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        // Declaración de variables
        int alturaMin;
        typename Agen<T>::nodo hijo;
        // Definición de variables
        alturaMin = alturaNodo(A,n);
        hijo = A.hijoIzqdo(n);

        while (hijo != Agen<T>::NODO_NULO)
        {
            alturaMin = min(alturaMin, alturaMinArbolRec(A, hijo) + 1);
            hijo = A.hermDrcho(hijo);
        }
        return alturaMin;
    }
}


template <typename T>
int alturaMinArbol(const Agen<T> &A)
{
    return alturaMinArbolRec(A, A.raiz());
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
    cout << "\nAltura del árbol A 'agen': " << alturaMinArbol(A) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);         // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nAltura del árbol B 'agen-ter': " << alturaMinArbol(B) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);         // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nAltura del árbol C 'agen-cua': " << alturaMinArbol(C) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);         // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nAltura del árbol D 'agen-abu': " << alturaMinArbol(D) << endl;
}