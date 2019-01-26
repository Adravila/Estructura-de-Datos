#include <iostream> 
#include <fstream> 
#include "abin_din.hpp" 
#include "abin_E-S.h"

using namespace std; 

template <typename T>
int contarNodosRec(const Abin<T>& A, typename Abin<T>::nodo n){
   if(n == Abin<T>::NODO_NULO)
      return 0;
   else
      return 1+contarNodosRec(A,A.hijoIzqdoB(n)) + contarNodosRec(A,A.hijoDrchoB(n));
}

template <typename T>
int contarNodos(const Abin<T>& A){
   contarNodosRec(A,A.raizB());
}

int main () { 
   Abin<char> A; 
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n"; 
   ifstream fe("abin.dat");   // abrir fichero de entrada 
   rellenarAbin(fe, A);       // desde fichero 
   fe.close(); 
   cout << "\n*** Mostrar árbol binario B ***\n"; 
   imprimirAbin(A);           // en std::cout 
   cout << "\nTotal de nodos del árbol: " << contarNodos(A) << endl;
} 