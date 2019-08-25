#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

template <typename T>
bool esAbuelo(typename Abin<T>::nodo n, Abin<T> &A)
{
    if (Abin<T>::NODO_NULO == n)
    {
        return true;
    }
    else
    {
        return (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && 
        ((A.hijoIzqdoB(A.hijoIzqdoB(n)) != Abin<T>::NODO_NULO) || A.hijoDrchoB(A.hijoIzqdoB(n)) != Abin<T>::NODO_NULO) ||
        (A.hijoDrchoB(n) != Abin<T>::NODO_NULO &&
        ((A.hijoIzqdoB(A.hijoDrchoB(n)) != Abin<T>::NODO_NULO) || A.hijoDrchoB(A.hijoDrchoB(n)) != Abin<T>::NODO_NULO)));
    }
}

template <typename T>
int contarAbuelosRec(typename Abin<T>::nodo n, Abin<T> &A)
{
    if (Abin<T>::NODO_NULO == n)
    {
        return 0;
    }
    else
    {
        int cont = 0;
        if (esAbuelo(n, A))
        {
            cout << A.elemento(n);
            ++cont;
        }
        return cont + contarAbuelosRec(A.hijoIzqdoB(n), A) + contarAbuelosRec(A.hijoDrchoB(n), A);
    }
}

template <typename T>
int contarAbuelos(Abin<T> &A)
{
    return contarAbuelosRec(A.raizB(), A);
}

int main()
{
   Abin<char> A;
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
   ifstream fe("abin.dat"); // abrir fichero de entrada
   rellenarAbin(fe, A);     // desde fichero
   fe.close();
   cout << "\n*** Mostrar árbol binario B ***\n";
   imprimirAbin(A); // en std::cout
   cout << "\nAbuelos que tiene el árbol: " << contarAbuelos(A) << endl;
}
