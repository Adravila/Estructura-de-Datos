#include <iostream> 
#include <fstream> 
#include "AGEN_H.h" 
#include "agen_E-S.h"

using namespace std; 

template <typename T>
int contarHijosRec(const Agen<T>& A, typename Agen<T>::nodo n){
	int cont = 0;
 	if(n == Agen<T>::NODO_NULO)		
 		return 0;
	else{
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO){
			cont++;
			hijo = A.hermDrcho(hijo);
		}
		return cont;
	}
}

template <typename T>
int contarHijos(const Agen<T>& A, typename Agen<T>::nodo n){
	if(!A.arbolVacio())
		return contarHijosRec(A,n);
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
   cout << "\nHijos de un nodo dado: " << contarHijos(A,A.hijoIzqdo(A.hijoIzqdo(A.raiz()))) << endl;
} 
