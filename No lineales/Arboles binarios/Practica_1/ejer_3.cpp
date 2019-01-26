#include <iostream> 
#include <fstream> 
#include "abin_din.hpp" 
#include "abin_E-S.h"

using namespace std; 

template <typename T>
int profundidadB(const Abin<T>& A, typename Abin<T>::nodo n){
   if(n == A.raizB())
      return 0;
   else
      return 1+profundidadB(A,A.padreB(n));
}

int main () { 
   Abin<char> A; 
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n"; 
   ifstream fe("abin.dat");   // abrir fichero de entrada 
   rellenarAbin(fe, A);       // desde fichero 
   fe.close(); 
   cout << "\n*** Mostrar árbol binario B ***\n"; 
   imprimirAbin(A);           // en std::cout 
   cout << "\nProfundidad de un árbol: " << profundidadB(A,(A.hijoDrchoB(A.hijoDrchoB(A.hijoDrchoB(A.raizB()))))) << endl;
} 