#include <iostream> 
#include <fstream> 
#include "AGEN_H.h" 
#include "agen_E-S.h"

using namespace std; 

template <typename T>
int contarNietosRec(const Agen<T>& A, typename Agen<T>::nodo n, int prof){
   int cont = 1;
   if(n == Agen<T>::NODO_NULO)      
      return 0;
   else{
      if(prof == 2)
         return 1+contarNietosRec(A,A.hijoIzqdo(n),prof+1)+contarNietosRec(A,A.hermDrcho(n),prof);
      return contarNietosRec(A,A.hijoIzqdo(n),prof+1)+contarNietosRec(A,A.hermDrcho(n),prof);
   }
}

template <typename T>
int contarNietos(const Agen<T>& A, typename Agen<T>::nodo n){
   if(!A.arbolVacio())
      return contarNietosRec(A,n,0);
   else
      return 0;
}

int main () { 
   Agen<char> A; 
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n"; 
   ifstream fe("abin.dat");   // abrir fichero de entrada 
   rellenarAgen(fe, A);       // desde fichero 
   fe.close(); 
   cout << "\n*** Mostrar árbol binario B ***\n"; 
   imprimirAgen(A);           // en std::cout 
   cout << "\nNietos de un nodo dado: " << contarNietos(A,A.raiz()) << endl;
} 
