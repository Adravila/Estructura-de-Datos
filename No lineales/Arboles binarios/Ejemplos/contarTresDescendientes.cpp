#include <iostream> 
#include <fstream> 
#include "abin_din.hpp" 
#include "abin_E-S.h"

using namespace std; 


template <typename T>
int contarDescendientes(const Abin<T>& A, typename Abin<T>::nodo n){
   if(n == Abin<T>::NODO_NULO)
      return 0;
   else
      return 1+contarDescendientes(A,A.hijoIzqdoB(n)) + contarDescendientes(A,A.hijoDrchoB(n));
}

template <typename T>
int contarTresDescendientesRec(const Abin<T>& A, typename Abin<T>::nodo n){
   if(n == Abin<T>::NODO_NULO)
      return 0;
   else{
      if(contarDescendientes(A,n)-1 == 3)
         return 1+contarTresDescendientesRec(A,A.hijoIzqdoB(n)) + contarTresDescendientesRec(A,A.hijoDrchoB(n));
      else
         return contarTresDescendientesRec(A,A.hijoIzqdoB(n)) + contarTresDescendientesRec(A,A.hijoDrchoB(n));
   }
}


template <typename T>
int contarTresDescendientes(const Abin<T>& A){
   if(!A.arbolVacioB())
      return contarTresDescendientesRec(A,A.raizB());
   else
      return 0;
}

int main () { 
   Abin<char> A; 
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n"; 
   ifstream fe("abin.dat");   // abrir fichero de entrada 
   rellenarAbin(fe, A);       // desde fichero 
   fe.close(); 
   cout << "\n*** Mostrar árbol binario B ***\n"; 
   imprimirAbin(A);           // en std::cout 
   cout << "\nTotal de nodos del árbol: " << contarTresDescendientes(A) << endl;
} 
