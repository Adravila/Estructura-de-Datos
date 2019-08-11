#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"

using namespace std;

// Comprobar si el nodo n tiene tres nietos

/*
template <typename T>
bool nodoConTresNietosRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
   int cont = 0;
   typename Abin<T>::nodo m;

   if (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO)
   {
      m = A.hijoIzqdoB(n);
      if(A.hijoIzqdoB(m) != Abin<T>::NODO_NULO) cont++;
      if(A.hijoDrchoB(m) != Abin<T>::NODO_NULO) cont++;
   }
   if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
   {
      m = A.hijoDrchoB(n);
      if(A.hijoIzqdoB(m) != Abin<T>::NODO_NULO) cont++;
      if(A.hijoDrchoB(m) != Abin<T>::NODO_NULO) cont++;
   }
   return cont == 3;
}


template <typename T>
bool nodoConTresNietos(const Abin<T> &A, typename Abin<T>::nodo n)
{
   if(A.arbolVacioB())
   {
      return nodoConTresNietosRec(A, n);
   }
   else
   {
      return false;
   }
}
*/

template <typename T>
int contarNietos(const Abin<T> &A, typename Abin<T>::nodo n, typename Abin<T>::nodo abuelo)
{
   int cont = 0;
   if (Abin<T>::NODO_NULO == n)
   {
      return 0;
   }
   else if (Abin<T>::NODO_NULO != n && Abin<T>::NODO_NULO != A.padreB(n) && abuelo == A.padreB(A.padreB(n)))
   {
      ++cont;
   }
   return cont + contarNietos(A, A.hijoIzqdoB(n), abuelo) + contarNietos(A, A.hijoDrchoB(n), abuelo);
}

template <typename T>
bool comprobarTresNietos(const Abin<T> &A, typename Abin<T>::nodo n)
{
   return (!A.arbolVacioB() && contarNietos(A, n, n) == 3);
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
   Abin<char> A;
   cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
   ifstream fe("abin.dat"); // abrir fichero de entrada
   rellenarAbin(fe, A);     // desde fichero
   fe.close();
   cout << "\n*** Mostrar árbol binario A ***\n";
   imprimirAbin(A); // en std::cout
   cout << "\nTiene tres nietos: " << comprobarTresNietos(A, (A.raizB())) << endl;
}