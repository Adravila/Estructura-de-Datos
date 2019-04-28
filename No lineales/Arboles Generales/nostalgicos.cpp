#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

template <typename T>
int profundidad(const Agen<T> &A, typename Agen<T>::nodo n)
{
    if (A.padre(n) == Agen<T>::NODO_NULO)
        return 0;
    else
        return 1 + profundidad(A, A.padre(n));
}

template <typename T>
int descendientes(const Agen<T> &A, typename Agen<T>::nodo n)
{
    int desc = 0;
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        desc++;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            desc += descendientes(A, hijo);
            hijo = A.hermDrcho(hijo);
        }
        return desc;
    }
}

template <typename T>
int NostalgicoRec(const Agen<T> &A, typename Agen<T>::nodo n)
{
    int nost = 0;
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if (profundidad(A, n) > descendientes(A, n) - 1) // Comprobar si es nostálgico (prof > desc)
        {
            nost++;
        }
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            nost += NostalgicoRec(A, hijo);
            hijo = A.hermDrcho(hijo);
        }
    }
    return nost;
}

template <typename T>
int Nostalgico(const Agen<T> &A)
{
    return NostalgicoRec(A, A.raiz());
}

int main()
{
    Agen<char> A, B, C, D;
    cout << "\n*** Lectura de árbol general A de agen.dat ***\n";
    ifstream fa("Data/agen.dat"); // abrir fichero de entrada
    rellenarAgen(fa, A);          // desde fichero
    fa.close();
    cout << "\n*** Mostrar árbol general A ***\n";
    imprimirAgen(A); // en std::cout
    cout << "\nEncontrar nodo con elemento 'h' en el árbol A 'agen': " << Nostalgico(A) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);              // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nEncontrar nodo con elemento 'h' en el árbol B 'agen-ter': " << Nostalgico(B) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);              // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nEncontrar nodo con elemento 'b' en el árbol C 'agen-cua': " << Nostalgico(C) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);              // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nEncontrar nodo con elemento 'x' en el árbol D 'agen-abu': " << Nostalgico(D) << endl;
}