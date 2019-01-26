#include <iostream> 
#include <fstream> 
#include "AGEN_H.h" 
#include "agen_E-S.h"

using namespace std; 

template <typename T>
int contarNodosRec(const Agen<T>& A, typename Agen<T>::nodo n){
	int cont = 0;
 	if(n == Agen<T>::NODO_NULO)		
 		return 0;
	else{
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO){
			hijo = A.hermDrcho(hijo);
		}
		cout << A.elemento(n);
		return 1+contarNodosRec(A,A.hijoIzqdo(n))+contarNodosRec(A,A.hermDrcho(n));
	}
}

template <typename T>
int contarNodos(const Agen<T>& A){
	if(!A.arbolVacio())
		return contarNodosRec(A,A.raiz());
	else
		return 0;
}

int main () { 
   Agen<char> A; 
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n"; 
   ifstream fe("abin.dat");   // abrir fichero de entrada 
   rellenarAgen(fe, A);       // desde fichero 
   fe.close(); 
   cout << "\n*** Mostrar árbol general A ***\n"; 
   imprimirAgen(A);           // en std::cout 
   cout << "\nNúmero de nodos del árbol A: " << contarNodos(A) << endl;
} 
