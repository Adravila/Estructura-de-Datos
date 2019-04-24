#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Calcular la densidad de un árbol general
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
int numHijos(const Agen<T> &A, typename Agen<T>::nodo n)
{
    typename Agen<T>::nodo hijo;
    int cont;
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        cont = 0;
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            cont++;
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

template <typename T>
int gradoArbol(const Agen<T> &A, typename Agen<T>::nodo n)
{
    typename Agen<T>::nodo hijo;
    hijo = A.hijoIzqdo(n);
    int Maxhijos = 0;
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        Maxhijos = numHijos(A, n);
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            Maxhijos = max(Maxhijos, gradoArbol(A, hijo));
            hijo = A.hermDrcho(hijo);
        }
        return Maxhijos;
    }
}

template <typename T>
int numNodosHoja(const Agen<T> &A, typename Agen<T>::nodo n)
{
    typename Agen<T>::nodo hijo;
    int cont = 0;
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        hijo = A.hijoIzqdo(n);
        if (hijo == Agen<T>::NODO_NULO)
        {
            ++cont;
        }

        while (hijo != Agen<T>::NODO_NULO)
        {
            cont += numNodosHoja(A, hijo);
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

template <typename T>
float densidad(const Agen<T> &A)
{
    return (float)gradoArbol(A, A.raiz()) / (float)numNodosHoja(A, A.raiz());
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
    cout << "\nDensidad del árbol A 'agen': " << densidad(A) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);         // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nDensidad del árbol B 'agen-ter': " << densidad(B) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);         // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nDensidad del árbol C 'agen-cua': " << densidad(C) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);         // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nDensidad del árbol D 'agen-abu': " << densidad(D) << endl;
}