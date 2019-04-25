#include <iostream>
#include <fstream>
#include "Cabeceras/abin_din.hpp"
#include "Cabeceras/abin_E-S.h"

using namespace std;

template <typename T>
bool sonDescendientes(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        bool esCierto = true;
        if (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO)
        {
            if (A.elemento(n) >= A.elemento(A.hijoIzqdoB(n)))
                esCierto = false;
        }
        if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
        {
            if (A.elemento(n) >= A.elemento(A.hijoDrchoB(n)))
                esCierto = false;
        }
        return esCierto && sonDescendientes(A.hijoIzqdoB(n), A) && sonDescendientes(A.hijoDrchoB(n), A);
    }
}
template <typename T>
int maxDesequilibrio(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
    {
        return max(max(abs(A.alturaB(A.hijoIzqdoB(n)) - A.alturaB(A.hijoDrchoB(n))), maxDesequilibrio(A.hijoIzqdoB(n), A)), maxDesequilibrio(A.hijoDrchoB(n), A));
    }
}

template <typename T>
bool esAPO(const Abin<T> &A)
{
    cout << "\nMax desequilibrio: " << maxDesequilibrio(A.raizB(), A) << endl;
    cout << "Son descendientes: ";
    sonDescendientes(A.raizB(), A) ? cout << "SÍ" << endl : cout << "NO" << endl;

    return maxDesequilibrio(A.raizB(), A) == 0 && sonDescendientes(A.raizB(), A);
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
    Abin<tElto> A;
    cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    ifstream fe("Data/abin-completo.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);          // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario A 'abin-completo.data' ***\n";
    imprimirAbin(A); // en std::cout
    cout << "\n¿Es esto un APO?: ";
    esAPO(A) ? cout << "SÍ, es un APO" << endl : cout << "NO, no es un APO" << endl;
}