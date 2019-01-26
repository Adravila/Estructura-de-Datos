#include "Agen.h"
#include <algorithm>

template <typename T>
int ramaLarga(const Agen<T>& A, typename Agen<T>::nodo n){
	if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
		return 0;
	else{
		int alturaMax = 0;
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO){
			alturaMax = std::max(alturaMax,ramaLarga(A,hijo)+1);
			hijo = A.hermDrcho(hijo);
		}
		return alturaMax;
	}
}

template <typename T>
int ramaCorta(const Agen<T>& A, typename Agen<T>::nodo n){
	if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
		return 0;
	else{
		int profMin = -1;
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO){
			profMin = std::max(profMin,ramaLarga(A,hijo)+1);
			hijo = A.hermDrcho(hijo);
		}
		return profMin;
	}
}
template <typename T>
int desequlibrioAgen(const Agen<T>& A){
	if(A.arbolVacio())
		return 0;
	else{
		int desequilibrioMax = 0;
		typename Agen<T>::nodo hijo = A.hijoIzqdo(A.raiz());
		while(hijo != Agen<T>::NODO_NULO){
			desequilibrioMax = std::max(desequilibrioMax,ramaLarga(A,hijo)-ramaCorta(A,hijo));
			hijo = A.hermDrcho(hijo);
		}
		return desequilibrioMax;
	}

}
