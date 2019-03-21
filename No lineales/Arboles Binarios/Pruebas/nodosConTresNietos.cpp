#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"

using namespace std;

// Comprobar si el nodo n tiene tres nietos

template <typename T>
bool comprobarTresNietos(const Abin<T> &A, typename Abin<T>::nodo n)
{
   int cont = 0;
   typename Abin<T>::nodo m;

   if((A.hijoIzqdoB(n) != Abin<T>::NODO_NULO) || (A.hijoDrchoB(n) != Abin<T>::NODO_NULO))
   {
      m = A.hijoIzqdoB(n);
      if(A.hijoIzqdoB(m) != Abin<T>::NODO_NULO) cont++;
      if(A.hijoDrchoB(m) != Abin<T>::NODO_NULO) cont++;
      m = A.hijoDrchoB(n);
      if(A.hijoIzqdoB(m) != Abin<T>::NODO_NULO) cont++;
      if(A.hijoDrchoB(m) != Abin<T>::NODO_NULO) cont++;
   }
   return cont == 3;
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
      if(comprobarTresNietos(n,A))
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
int nodoConTresNietos(const Abin<T> &A)
{
   return nodoConTresNietosRec(A, A.raizB());
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
   Abin<tElto> A, B;
   /*
   cout << "*** Lectura del árbol binario A ***\n";
   rellenarAbin(A, fin); // desde std::cin
   ofstream fs("abin.dat"); // abrir fichero de salida
   imprimirAbin(fs, A, fin); // en fichero
   fs.close();
   cout << "\n*** Árbol A guardado en fichero abin.dat ***\n";
   */
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
   ifstream fe("abin.dat"); // abrir fichero de entrada
   rellenarAbin(fe, B);     // desde fichero
   fe.close();
   cout << "\n*** Mostrar árbol binario B ***\n";
   imprimirAbin(B); // en std::cout

   cout << "\nAltura arbol: " << nodoConTresNietos(B,A.raizB()) << endl;
}