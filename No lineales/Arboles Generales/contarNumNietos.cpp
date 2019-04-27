#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Contar los nodos que tienen n nietos de todo el árbol
 * Creado por: Adrián Dávila Guerra ©
 * 27/04/2019
**/

template <typename T>
int numNietos(typename Agen<T>::nodo n, const Agen<T> &A, int prof)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return false;
    }
    else
    {
        typename Agen<T>::nodo hijo;
        int cont;

        cont = 0;
        hijo = A.hijoIzqdo(n);

        if(prof == 2)
        {
            ++cont;
        }

        while (hijo != Agen<T>::NODO_NULO)
        {
            cont += numNietos(hijo,A,prof+1);
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

template <typename T>
int contarNumNietosRec(typename Agen<T>::nodo n, const Agen<T> &A, int grado)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int cont = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);

        if (numNietos(n, A, 0) == grado)
        {
            cout << A.elemento(n);
            ++cont;
        }
        while (hijo != Agen<T>::NODO_NULO)
        {
            cont += contarNumNietosRec(hijo, A, grado);
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

template <typename T>
int contarNumNietos(const Agen<T> &A, int grado)
{
    return contarNumNietosRec(A.raiz(), A, grado);
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
    cout << "\nCantidad de nodos que son abuelos y nietos en el árbol A 'agen': " << contarNumNietos(A,3) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);              // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nCantidad de nodos que son abuelos y nietos en el árbol B 'agen-ter': " << contarNumNietos(B,6) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);              // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nCantidad de nodos que son abuelos y nietos en el árbol C 'agen-cua': " << contarNumNietos(C,8) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);              // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nCantidad de nodos que son abuelos y nietos en el árbol D 'agen-abu': " << contarNumNietos(D,3) << endl;
}