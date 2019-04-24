#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Calcular el grado de desequilibrio de todo el árbol general
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
int altura(typename Agen<T>::nodo n,const Agen<T> &A)
{
    if (A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        int alturaMax = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            alturaMax = max(alturaMax, altura(hijo,A) + 1);
            hijo = A.hermDrcho(hijo);
        }
        return alturaMax;
    }
}

template <typename T>
int desequilibrioAgen(const Agen<T> &A)
{
    if (A.arbolVacio())
    {
        return 0;
    }
    else
    {
        int desequilibrioMax = 0;
        int desequilibrioMin = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(A.raiz());
        while (hijo != Agen<T>::NODO_NULO)
        {
            desequilibrioMax = max(desequilibrioMax, altura(hijo,A));
            desequilibrioMin = min(desequilibrioMax, altura(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return abs(desequilibrioMax - desequilibrioMin);
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
    cout << "\nDesequilibrio del árbol A 'agen': " << desequilibrioAgen(A) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);         // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nDesequilibrio del árbol B 'agen-ter': " << desequilibrioAgen(B) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);         // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nDesequilibrio del árbol C 'agen-cua': " << desequilibrioAgen(C) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);         // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nDesequilibrio del árbol D 'agen-abu': " << desequilibrioAgen(D) << endl;
}