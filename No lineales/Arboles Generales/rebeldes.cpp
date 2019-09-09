#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/* Se dice de nodo rebelde aquel cuyas ideas son diferentes a la de la mayoría de sus ancestros.
Dado un árbol binario cualquiera calcular el número de nodos rebeldes de dicho árbol.
Ejemplo: si el nodo vale '1' y tiene tres ancestros que valen '1' y seis que valen '0', es rebelde. */

template <typename T>
int contarAncestros(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n != A.raiz() || n != Agen<T>::NODO_NULO)
    {
        return 1 + contarAncestros(A.padre(n),A);
    }
}

template <typename T>
int num_true(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else if (A.elemento(A.padre(n)))
        return 1 + num_true(A.padre(n), A);
    else
        return num_true(A.padre(n), A);
}

template <typename T>
bool esRebelde(typename Agen<T>::nodo n, const Agen<T> &A)
{

    if (A.elemento(n) == true)
    {
        return (contarAncestros(n, A) / 2) > (num_true(n, A));
    }
    else
    {
        return false;
    }
}

template <typename T>
int contarRebeldesRec(const Agen<T> &A, typename Agen<T>::nodo n)
{
    int cont = 0;
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            if (esRebelde(hijo,A))
            {
                cont++;
            }
            cont += contarRebeldesRec(A, hijo);
            hijo = A.hermDrcho(hijo);
        }
    }
    return cont;
}

template <typename T>
int contarRebeldes(const Agen<T> &A)
{
    return contarRebeldesRec(A, A.raiz());
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
    cout << "\nEncontrar nodo con elemento 'h' en el árbol A 'agen': " << contarRebeldes(A) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);              // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nEncontrar nodo con elemento 'h' en el árbol B 'agen-ter': " << contarRebeldes(B) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);              // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nEncontrar nodo con elemento 'b' en el árbol C 'agen-cua': " << contarRebeldes(C) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);              // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nEncontrar nodo con elemento 'x' en el árbol D 'agen-abu': " << contarRebeldes(D) << endl;
}