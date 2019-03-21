#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"
#include <map>

using namespace std;

template <typename T>
int contarHijosDrchoRec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
        {
            return 1 + contarHijosDrchoRec(A.hijoIzqdoB(n),A) + contarHijosDrchoRec(A.hijoDrchoB(n),A);
        }
        else
        {
            return 0 + contarHijosDrchoRec(A.hijoIzqdoB(n),A) + contarHijosDrchoRec(A.hijoDrchoB(n),A);
        }
    }
}

template <typename T>
int contarHijosDrcho(const Abin<T>& A)
{
    return contarHijosDrchoRec(A.raizB(),A);
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
   Abin<tElto> A;
   cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
   ifstream fe("abin.dat"); // abrir fichero de entrada
   rellenarAbin(fe, A);     // desde fichero
   fe.close();
   cout << "\n*** Mostrar árbol binario A ***\n";
   imprimirAbin(A); // en std::cout

   cout << "\nCantidad de hijos derechos del árbol: " << contarHijosDrcho(A) << endl;
}