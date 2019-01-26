#include "Agen.h"
#include <iostream>
#include <algorithm>

template <typename T>
int numHijos(const Agen<T>& A, typename Agen<T>::nodo n){
	typename Agen<T>::nodo hijo;
	int cont;
	if(n == Agen<T>::NODO_NULO)
		return 0;
	else{
		cont = 0;
		hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO){
			cont++;
			hijo = A.hermDrcho(hijo);
		}
		return cont;
	}
}

template <typename T>
int gradoArbol(const Agen<T>& A, typename Agen<T>::nodo n){
	typename Agen<T>::nodo hijo;
	hijo = A.hijoIzqdo(n);
	int Maxhijos = 0;
	if(n == Agen<T>::NODO_NULO)
		return 0;
	else{
		Maxhijos = numHijos(A,n);
		hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO){
			Maxhijos = std::max(Maxhijos,gradoArbol(A,hijo));
			hijo = A.hermDrcho(hijo);
		}
		return Maxhijos;
	}
}

template <typename T>
int numNodosHoja(const Agen<T>& A, typename Agen<T>::nodo n){
	typename Agen<T>::nodo hijo;
	int cont = 0;
	if(n == Agen<T>::NODO_NULO)
		return 0;
	else{
		hijo = A.hijoIzqdo(n);
		if(hijo == Agen<T>::NODO_NULO)
			cont++;
		else{
			while(hijo != Agen<T>::NODO_NULO){
				cont += numNodosHoja(A,A.hermDrcho(hijo));
				hijo = A.hermDrcho(hijo);
			}
			cont += numNodosHoja(A,A.hijoIzqdo(n));
		}
        return cont;
	}
}

template <typename T>
float densidad(const Agen<T>& A){
	if(!A.arbolVacio())
		return (float)gradoArbol(A,A.raiz()) / (float)numNodosHoja(A,A.raiz());
}
