#include <iostream> 
#include <fstream> 
#include "AGEN_H.h" 
#include "agen_E-S.h"

using namespace std; 

template <typename T>
int contarNietosRec(const Agen<T>& A, typename Agen<T>::nodo n, int prof){
	int cont = 0;
 	if(n == Agen<T>::NODO_NULO)		
 		return 0;
	else{
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO && prof == 2){
			cont++;
			hijo = A.hermDrcho(hijo);
		}
		return cont+contarNietosRec(A,A.hijoIzqdo(n),prof+1);
	}
}

template <typename T>
int contarNietos(const Agen<T>& A, typename Agen<T>::nodo n){
	if(!A.arbolVacio())
		return contarNietosRec(A,n,1);
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
