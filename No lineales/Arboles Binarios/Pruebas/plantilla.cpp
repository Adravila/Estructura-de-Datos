#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

template <typename T>
int contarNodos(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + contarNodos(A.hijoIzqdoB(n), A) + contarNodos(A.hijoDrchoB(n), A);
    }    
}

template <typename T>
int tresDescendientesRec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int cont = 0;
        if (contarNodos(n,A) - 1 == 3)
            cont = 1;
        return cont + tresDescendientesRec(A.hijoIzqdoB(n), A) + tresDescendientesRec(A.hijoDrchoB(n), A);
    }
}


template <typename T>
int tresDescendientes(const Abin<T>& A)
{
    return tresDescendientesRec(A.raizB(), A);
}

int main()
{
    Abin<char> A;
    cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    ifstream fe("abin.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);     // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); // en std::cout
    cout << "Abuelos totales: " << tresDescendientes(A) << endl;
}