#include <algorithm>
#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "Cola_enla.h"

template <typename T>
bool pseudocompletoRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else if ((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) || 
            (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
    {
         return false;
    }
    else
    {
        return pseudocompletoRec(A,A.hijoIzqdoB(n)) && pseudocompletoRec(A,A.hijoDrchoB(n));
    }
    
     
}

// Recorrido en anchura (clase)
template <typename T>
bool pseudocompletoAnchura(const Abin<T> &A, typename Abin<T>::nodo n)
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
            if ((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && A.hijoDrchoB(n) == Abin<T>::NODO_NULO) ||
                (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
            {
                return false;
            }
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
        //return pseudocompletoAnchura(A, A.raizB());
        return pseudocompletoRec(A,A.raizB());
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
