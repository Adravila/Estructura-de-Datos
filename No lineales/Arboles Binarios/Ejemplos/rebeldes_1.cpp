#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"

using namespace std;

template <typename T>
int esRebelde(typename Abin<T>::nodo n, typename Abin<T>::nodo acusado, const Abin<T>& A)
{
    if(n == A.raizB())
    {
        return 0;
    }
    else
    {
        if(A.elemento(A.padreB(n)) == A.elemento(acusado))
        {
            return 1 + esRebelde(A.padreB(n),acusado,A);
        }
        else
        {
            return -1 + esRebelde(A.padreB(n),acusado,A);
        }
        
    }
}

template <typename T>
int contarNodosRebeldes(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
                cout << A.elemento(n) << "..." << esRebelde(n,n,A);

        if(esRebelde(n,n,A) < 0)
        {
            return 1 + contarNodosRebeldes(A.hijoIzqdoB(n),A) + contarNodosRebeldes(A.hijoDrchoB(n),A);
        }
        else
        {
            return 0 + contarNodosRebeldes(A.hijoIzqdoB(n),A) + contarNodosRebeldes(A.hijoDrchoB(n),A);
        }
    }
}

template <typename T>
int contarNodosRebeldes(const Abin<T>& A)
{
    return contarNodosRebeldes(A.raizB(),A);
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
   Abin<tElto> A;
   cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
   ifstream fe("abin-rebeldes.dat"); // abrir fichero de entrada
   rellenarAbin(fe, A);     // desde fichero
   fe.close();
   cout << "\n*** Mostrar árbol binario A ***\n";
   imprimirAbin(A); // en std::cout

   cout << "\nCantidad de nodos con tres nietos: " << contarNodosRebeldes(A) << endl;
}