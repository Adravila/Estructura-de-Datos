#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "Pila_enla.h"

using namespace std;

// Forma recursiva (preorden en profundidad)
template <typename T>
int contarNodosRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
   if (n == Abin<T>::NODO_NULO)
      return 0;
   else
      return 1 + contarNodosRec(A, A.hijoIzqdoB(n)) + contarNodosRec(A, A.hijoDrchoB(n));
}

// Forma iterativa (preorden en profundidad)
template <typename T>
int contarNodosIte(const Abin<T> &A, typename Abin<T>::nodo n)
{
   Pila<typename Abin<T>::nodo> P; // pila de nodos de árbol binario
   int cont = 0;
   do
   {
      if (n != Abin<T>::NODO_NULO)
      {
         ++cont; // Procesar
         if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
            P.push(A.hijoDrchoB(n));
         n = A.hijoIzqdoB(n);
      }
      else if (!P.vacia())
      {
         n = P.tope();
         P.pop();
      }
   } while (!(n == Abin<T>::NODO_NULO && P.vacia()));
   return cont;
}

template <typename T>
int contarNodos1(const Abin<T> &A)
{
   return contarNodosRec(A, A.raizB());
}

template <typename T>
int contarNodos2(const Abin<T> &A)
{
   return contarNodosIte(A, A.raizB());
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

   cout << "\nContar nodos: " << contarNodos1(B) << endl;
}