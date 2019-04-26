#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Encontrar un elemento del árbol general
 * Creado por: Adrián Dávila Guerra ©
 * 26/04/2019
**/

template <typename T>
typename Agen<T>::nodo buscarNodoAgen(typename Agen<T>::nodo n, const Agen<T> &A, const T &elto)
{
    if (n == Agen<T>::NODO_NULO || A.elemento(n) == elto)
    {
        return n;
    }
    else
    {
        typename Agen<T>::nodo aux;
        aux = buscarNodoAgen(A.hijoIzqdo(n), A, elto);
        if (aux == Agen<T>::NODO_NULO && n != A.raiz())
        {
            return buscarNodoAgen(A.hermDrcho(n), A, elto);
        }
        else
        {
            return aux;
        }
    }
}

template <typename T>
const char *buscarNodo(char elto, const Agen<T> &A)
{
    typename Agen<T>::nodo aux = buscarNodoAgen(A.raiz(), A, elto);
    (aux != Agen<T>::NODO_NULO) ? cout << "Se ha encontrado " << elto : cout << "No se ha encontrado " << elto;
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
    cout << "\nEncontrar nodo con elemento 'h' en el árbol A 'agen': " << buscarNodo('h', A) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);              // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nEncontrar nodo con elemento 'h' en el árbol B 'agen-ter': " << buscarNodo('o', B) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);              // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nEncontrar nodo con elemento 'b' en el árbol C 'agen-cua': " << buscarNodo('b', C) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);              // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nEncontrar nodo con elemento 'x' en el árbol D 'agen-abu': " << buscarNodo('x', D) << endl;
}