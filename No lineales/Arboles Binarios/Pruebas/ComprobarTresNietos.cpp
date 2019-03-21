#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"

using namespace std;

// Comprobar si el nodo n tiene tres nietos

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

   cout << "\nÁrbol con tres nietos: " << nodoConTresNietos(B,A.raizB()) << endl;
}