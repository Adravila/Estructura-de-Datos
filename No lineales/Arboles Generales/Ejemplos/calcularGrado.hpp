#include "Agen.h"
#include <algorithm>

template <typename T>
int numHijos(const Agen<T>& A, typename Agen<T>::nodo n){
	typename Agen<T>::nodo hijo;
	int numNodos = 0;
    hijo = A.hijoIzqdo(n);
    while(hijo != Agen<T>::NODO_NULO){
        ++numNodos;
        hijo = A.hermDrcho(hijo);
    }
    return numNodos;
}

template <typename T>
int gradoAgenRec(const Agen<T>& A, typename Agen<T>::nodo n){
	typename Agen<T>::nodo hijo;
	int gradoMax = numHijos(A,n);
    hijo = A.hijoIzqdo(n);

	if(hijo == Agen<T>::NODO_NULO)
		return 0;
    else
        while(hijo != Agen<T>::NODO_NULO){
            gradoMax = std::max(gradoMax,gradoAgenRec(A,hijo));
            hijo = A.hermDrcho(hijo);
    }
    return gradoMax;
}

template <typename T>
int gradoAgen(const Agen<T>& A){
    if(A.arbolVacio())
        return 0;
    else
        return gradoAgenRec(A,A.raiz());
}
