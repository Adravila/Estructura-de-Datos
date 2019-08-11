#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

/*
template <typename T>
int contarNietosRec(const Abin<T>& A, typename Abin<T>::nodo n, int prof){
   if(n == Abin<T>::NODO_NULO)
      return 0;
   if(prof == 2) // Contar nietos | Nota: 1 contar hijos, 2 contar nietos, 3 contar bisnietos, etc...
      return 1;
   else
      return contarNietosRec(A,A.hijoIzqdoB(n),prof+1)+contarNietosRec(A,A.hijoDrchoB(n),prof+1);
}

template <typename T>
int contarNietos(const Abin<T>& A, typename Abin<T>::nodo n){
   if(!A.arbolVacioB())
      return contarNietosRec(A,n,0);
   else
      return 0;
}
*/

template <typename T>
int contarNietosRec(const Abin<T> &A, typename Abin<T>::nodo n, typename Abin<T>::nodo abuelo)
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
   return cont + contarNietosRec(A, A.hijoIzqdoB(n), abuelo) + contarNietosRec(A, A.hijoDrchoB(n), abuelo);
}

template <typename T>
int contarNietos(const Abin<T> &A, typename Abin<T>::nodo n)
{
   if (!A.arbolVacioB())
      return contarNietosRec(A, n, n);
   else
      return 0;
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
   cout << "\nNietos de un nodo dado: " << contarNietos(A, (A.raizB())) << endl;
}
