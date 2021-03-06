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
void eliminarDescendientes(typename Agen<T>::nodo n, Agen<T> &A)
{
    if (n != Agen<T>::NODO_NULO)
    {
        typename Agen<T>::nodo hijo;
        hijo = A.hijoIzqdo(n);
        
        while (hijo != Agen<T>::NODO_NULO)
        {
            eliminarDescendientes(hijo, A);
            hijo = A.hermDrcho(hijo);
            A.eliminarHijoIzqdo(n);
        }
    }
}

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
void podarArbol(Agen<T> &A, const T &elto)
{
    typename Agen<T>::nodo aux = buscarNodoAgen(A.raiz(), A, elto);
    typename Agen<T>::nodo elim;
    if (aux != Agen<T>::NODO_NULO)
    {
        // Eliminar descendientes del nodo encontrado
        eliminarDescendientes(aux, A);
        // En este proceso tendremos que eliminar el nodo desde otro, es decir, empezando desde el hijo izquierdo de su padre
        elim = A.hijoIzqdo(A.padre(aux));
        // Si el nodo a eliminar es el hijo izquierdo
        if (elim != Agen<T>::NODO_NULO || A.elemento(aux) == A.elemento(elim))
        {
            A.eliminarHijoIzqdo(A.padre(aux));
        }
        // Si el nodo a eliminar es el hijo
        while (elim != Agen<T>::NODO_NULO)
        {
            if (A.hermDrcho(elim) != Agen<T>::NODO_NULO)
            {
                if (A.elemento(aux) == A.elemento(A.hermDrcho(elim)))
                {
                    A.eliminarHermDrcho(elim);
                }
            }
            elim = A.hermDrcho(elim);
        }
    }
    else
    {
        cout << "No se ha encontrado un elemento del árbol para podar" << endl;
    }
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
    podarArbol(A, 'g');
    cout << endl
         << "Arbol modificado: " << endl;
    imprimirAgen(A); // en std::cout
}