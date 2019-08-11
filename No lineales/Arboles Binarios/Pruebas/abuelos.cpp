#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

template <typename T>
int contarAbuelosRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
    int cont = 0;
    if (Abin<T>::NODO_NULO == n)
    {
        return 0;
    }
    else if (Abin<T>::NODO_NULO != n && Abin<T>::NODO_NULO != A.padreB(n) && Abin<T>::NODO_NULO != A.padreB(A.padreB(n)))
    {
        ++cont;
    }
    return cont + contarAbuelosRec(A, A.hijoIzqdoB(n)) + contarAbuelosRec(A, A.hijoDrchoB(n));
}

template <typename T>
int contarAbuelos(const Abin<T> &A)
{
    return contarAbuelosRec(A,A.raizB());
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
