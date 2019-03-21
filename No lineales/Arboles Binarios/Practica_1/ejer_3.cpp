#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

// Forma recursiva
template <typename T>
int profundidadBRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
   if (n == A.raizB())
      return 0;
   else
      return 1 + profundidadBRec(A.padreB(n),A);
}

// Forma iterativa
template <typename T>
int profundidadBIte(typename Abin<T>::nodo n, const Abin<T> &A)
{
   int cont = 0;
   while (n != A.raizB())
   {
      n = A.padreB(n);
      ++cont;
   }
   return cont;
}

int main()
{
   Abin<char> A;
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
   ifstream fe("abin.dat"); // abrir fichero de entrada
   rellenarAbin(fe, A);     // desde fichero
   fe.close();
   cout << "\n*** Mostrar árbol binario B ***\n";
   imprimirAbin(A); // en std::cout
   cout << "\nProfundidad de un árbol: " << profundidadBRec(A.hijoDrchoB(A.hijoDrchoB(A.hijoDrchoB(A.raizB()))),A) << endl;
}