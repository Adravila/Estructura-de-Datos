#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"

// REVISADO POR DE LA HUERTA

using namespace std;

template <typename T>
int contarNodos(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + contarNodos(A.hijoIzqdoB(n), A) + contarNodos(A.hijoDrchoB(n), A);
    }
}

template <typename T>
bool comprobarEsNieto(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (A.padreB(n) != Abin<T>::NODO_NULO)
    {
        return A.padreB(A.padreB(n)) != Abin<T>::NODO_NULO;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool comprobarEsAbuelo(typename Abin<T>::nodo n, int iter, const Abin<T> &A)
{
    if( n == Abin<T>::NODO_NULO)
    {
        return false;
    }
    else
    {

        if(iter == 1)
        {
            return true;
        }
        else
        {
            ++iter;
            return comprobarEsAbuelo(A.hijoIzqdoB(n), iter, A) && comprobarEsAbuelo(A.hijoDrchoB(n), iter, A);
        }
    }
    
    /**
    if (iter)
    {
        --iter;
        return comprobarEsAbuelo(A.hijoIzqdoB(n), iter, A) && comprobarEsAbuelo(A.hijoDrchoB(n), iter, A);
    }
    else
    {
        if (n == Abin<T>::NODO_NULO)
        {
            return false;
        }
        else
        {
                    cout << A.elemento(n);

            return true;
        }
    }
    **/
}

template <typename T>
int numAbuelosNietosRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if (comprobarEsAbuelo(n, 0, A) && comprobarEsNieto(n, A))
        {
            return 1 + numAbuelosNietosRec(A.hijoIzqdoB(n), A) + numAbuelosNietosRec(A.hijoDrchoB(n), A);
        }
        else
        {
            return 0 + numAbuelosNietosRec(A.hijoIzqdoB(n), A) + numAbuelosNietosRec(A.hijoDrchoB(n), A);
        }
    }
}

template <typename T>
float numAbuelosNietos(const Abin<T> &A)
{
    return ((float)numAbuelosNietosRec(A.raizB(), A) / (float)contarNodos(A.raizB(), A)) * 100;
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
    Abin<tElto> B;
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("abin.dat"); // abrir fichero de entrada
    rellenarAbin(fe, B);     // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(B); // en std::cout

    cout << "\nProporción de nodos que son nietos y a abuelos a la vez: " << numAbuelosNietos(B) << "%" << endl;
}