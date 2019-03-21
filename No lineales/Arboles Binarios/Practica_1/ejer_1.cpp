#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "Pila_enla.h"

using namespace std;

// Forma recursiva (preorden en profundidad)
template <typename T>
int contarNodosRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
   if (n == Abin<T>::NODO_NULO)
      return 0;
   else
      return 1 + contarNodosRec(A.hijoIzqdoB(n),A) + contarNodosRec(A.hijoDrchoB(n),A);
}

template <typename T>
int contarNodos(const Abin<T> &A)
{
   return contarNodosRec(A.raizB(),A);
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

   cout << "\nContar nodos: " << contarNodos(B) << endl;
}