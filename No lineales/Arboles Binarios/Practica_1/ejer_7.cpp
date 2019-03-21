#include <algorithm>
#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "Cola_enla.h"

template <typename T>
bool pseudocompletoRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO && A.alturaB(n) == 0)
    {
        return true;
    }
    else if (A.alturaB(n) == 1)
    {
        if ((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) ||
            (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else if (A.alturaB(A.hijoIzqdoB(n)) > A.alturaB(A.hijoDrchoB(n)))
    {
        return pseudocompletoRec(A.hijoIzqdoB(n), A);
    }
    else if (A.alturaB(A.hijoIzqdoB(n)) < A.alturaB(A.hijoDrchoB(n)))
    {
        return pseudocompletoRec(A.hijoDrchoB(n), A);
    }
    else
    {
        return pseudocompletoRec(A.hijoIzqdoB(n), A) && pseudocompletoRec(A.hijoDrchoB(n), A);
    }
}

// Recorrido en anchura (clase)
template <typename T>
bool pseudocompletoAnchura(typename Abin<T>::nodo n, const Abin<T> &A)
{
    Cola<typename Abin<T>::nodo> C; // cola de nodos de árbol binario
    if (n != Abin<T>::NODO_NULO)
    {
        do
        {
            if (!C.vacia())
            {
                n = C.frente();
                C.pop();
            }
            // Procesar
            if (n == Abin<T>::NODO_NULO && A.alturaB(n) == 0)
            {
                return true;
            }
            else if (A.alturaB(n) - A.profundidadB(n) == -1)
            {
                if ((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) ||
                    (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            // Fin Procesar
            if (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO)
                C.push(A.hijoIzqdoB(n));
            if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
                C.push(A.hijoDrchoB(n));
        } while (!C.vacia());
    }
    return true;
}

template <typename T>
bool pseudocompleto(const Abin<T> &A)
{
    if (!A.arbolVacioB())
    {
        return pseudocompletoAnchura(A.raizB(),A);
        //return pseudocompletoRec(A.raizB(), A);
    }
    else
        return false;
}

using namespace std;

int main()
{
    Abin<char> A;
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("abin_2.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);     // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(A); // en std::cout
    cout << "Este árbol es pseudocompleto: " << pseudocompleto(A) << endl;
}
