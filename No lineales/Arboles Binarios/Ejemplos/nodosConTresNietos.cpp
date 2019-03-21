#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"

using namespace std;

// Comprobar si el nodo n tiene tres nietos

template <typename T>
int contarNietos(typename Abin<T>::nodo n, const Abin<T> &A, int iter)
{
   if(n == Abin<T>::NODO_NULO)
   {
      return 0;
   }
   else
   {
      if(iter == 2)
      {
         return 1;
      }
      else
      {
         ++iter;
         return contarNietos(A.hijoIzqdoB(n),A,iter) + contarNietos(A.hijoDrchoB(n),A,iter);
      }
      
   }
}

template <typename T>
int contarTresNietosRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
   if(n == Abin<T>::NODO_NULO)
   {
      return 0;
   }
   else
   {
      if(contarNietos(n,A,0) == 4)
      {
         return 1 + contarTresNietosRec(A.hijoIzqdoB(n),A) + contarTresNietosRec(A.hijoDrchoB(n),A);
      }
      else
      {
         return 0 + contarTresNietosRec(A.hijoIzqdoB(n),A) + contarTresNietosRec(A.hijoDrchoB(n),A);
      }
   }
}

template <typename T>
int contarTresNietos(const Abin<T> &A)
{
   return contarTresNietosRec(A.raizB(),A);
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

   cout << "\nCantidad de nodos con tres nietos: " << contarTresNietos(A) << endl;
}