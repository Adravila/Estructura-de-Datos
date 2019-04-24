#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Comprobar si todos los nodos del árbol tienen 4 hijos o ninguno
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
bool esArbolTernarioRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
    int cont;
    typename Agen<T>::nodo hijo;
    if (n == Agen<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        cont = 0;
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            if (!esArbolTernarioRec(hijo, A))
            {
                return false;
            }
            ++cont;
            hijo = A.hermDrcho(hijo);
        }
        return (cont == 3 || cont == 0);
    }
}

template <typename T>
bool esArbolTernarioRec2(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if (numHijos(n, A) == 3 || A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        {
            return esArbolTernarioRec2(A.hijoIzqdo(n), A) && esArbolTernarioRec(A.hermDrcho(n), A);
        }
        else
        {
            return false;
        }
    }
}

template <typename T>
bool esArbolTernario(const Agen<T> &A)
{
    if (!A.arbolVacio())
    {
        esArbolTernarioRec(A.raiz(), A);
    }
    else
    {
        return false;
    }
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
    cout << "Este árbol es un árbol estrictamente ternario: ";
    if (esArbolTernario(A))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);         // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "Este árbol es un árbol estrictamente ternario: ";
    if (esArbolTernario(B))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);         // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "Este árbol es un árbol estrictamente ternario: ";
    if (esArbolTernario(C))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);         // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "Este árbol es un árbol estrictamente ternario: ";
    if (esArbolTernario(D))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }
}