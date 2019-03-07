#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"

using namespace std;

template <typename T>
int alturaArbolRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
   if (n == Abin<T>::NODO_NULO)
      return -1;
   else
      return 1 + max(alturaArbolRec(A, A.hijoIzqdoB(n)), alturaArbolRec(A, A.hijoDrchoB(n)));
}

template <typename T>
int alturaArbol(const Abin<T> &A)
{
   alturaArbolRec(A, A.raizB());
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

   cout << "\nAltura arbol: " << alturaArbol(B) << endl;
}